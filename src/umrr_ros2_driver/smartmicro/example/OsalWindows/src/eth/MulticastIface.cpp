/************************************************************************
 * Copyright
 *
 * s.m.s. smart microwave sensors GmbH
 * In den Waashainen 1
 * 38108 Braunschweig - Germany
 *
 * Register Court: Amtsgericht Braunschweig / Register Number: HRB 4525
 * VAT ID: DE 193324798 / Tax Number: 13/207/02357
 ************************************************************************/

#include <MulticastIface.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ws2tcpip.h>

using namespace osal::types;
using namespace osal;

const size_t MAX_BUFF_SIZE = 256U;
const std::string MULTI_NETMASK = "255.255.0.0";

MulticastIface::MulticastIface(const std::string &ip, uint32_t port,
                               const std::string &ethInterface)
    : EthIface(ip, port), _interface(ethInterface), _socket(-1),
      _buffer(new char[MAX_BUFF_SIZE]) {}

MulticastIface::~MulticastIface() {
  Stop();
  struct ip_mreq_source imr;
  InetPton(AF_INET, GetRxIpAddr().c_str(), &imr.imr_multiaddr.s_addr);
  imr.imr_sourceaddr.s_addr = htonl(INADDR_ANY);
  InetPton(AF_INET, _interface.c_str(), &imr.imr_interface.s_addr);
  if (0 > setsockopt(_socket, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&imr,
                     sizeof(imr))) {
    printf("Failed to drop mulitcast option \n");
  }
  closesocket(_socket);
  delete[] _buffer;
}

bool MulticastIface::Init() {
  bool retVal = false;
  retVal = joinGrp();
  return retVal;
}

bool MulticastIface::Start() {
  _isRun = true;
  _thread = std::thread(&MulticastIface::receiver, this);
  _thread.detach();
  return true;
}

void MulticastIface::Stop() { _isRun = false; }

bool MulticastIface::RegisterReceiver(IN const std::string &ip,
                                      IN ReceiverCallback callback) {
  _callback = callback;
  return true;
}

bool MulticastIface::UnRegisterReceiver(IN const std::string &ip) {
  _callback = nullptr;
  return true;
}

void MulticastIface::receiver() {
  while (_isRun) {
    sockaddr_in src;
    socklen_t srcLen = sizeof(src);

    auto received =
        recvfrom(_socket, _buffer, MAX_BUFF_SIZE, 0,
                 reinterpret_cast<struct sockaddr *>(&src), &srcLen);
    if (0 < received) {
      if (_callback) {
        BufferDescriptor desc(reinterpret_cast<uint8_t *>(_buffer), received);
        _callback(desc);
      }
    }
  }
}

bool MulticastIface::SendData(IN const std::string &, IN uint16_t,
                              IN BufferDescriptor desc) {
  bool retVal = true;
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  InetPton(AF_INET, GetRxIpAddr().c_str(), &addr.sin_addr.s_addr);
  addr.sin_port = htons(GetRxPort());
  int sent = sendto(_socket, reinterpret_cast<char *>(desc.GetBufferPtr()),
                    static_cast<int>(desc.GetSize()), 0,
                    (struct sockaddr *)&addr, sizeof(addr));

  if (sent != desc.GetSize()) {
    printf("Only [%d] byts were sent \n", sent);
    retVal = false;
  }
  return retVal;
}

bool MulticastIface::joinGrp() {
  bool retVal = true;
  _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (0 > _socket) {
    printf("Failed to create a socket %i \n", WSAGetLastError());
    retVal = false;
  }

  if (retVal) {
    char value = 1;
    if (0 >
        setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value))) {
      printf("Failed to set reuse option \n");
      retVal = false;
    }
  }

  if (retVal) {
    struct in_addr localInterface;
    InetPton(AF_INET, _interface.c_str(), &localInterface.s_addr);
    if (setsockopt(_socket, IPPROTO_IP, IP_MULTICAST_IF,
                   (char *)&localInterface, sizeof(localInterface)) < 0) {
      printf("Failed to set multicast interface");
      retVal = false;
    }
  }

  if (retVal) {
    char disable_loop = 0;
    if (setsockopt(_socket, IPPROTO_IP, IP_MULTICAST_LOOP,
                   (char *)&disable_loop, sizeof(disable_loop)) < 0) {
      printf("Failed to disable multicast loopback");
      retVal = false;
    }
  }

  if (retVal) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(_port);
    if (0 > bind(_socket, (struct sockaddr *)&addr, sizeof(addr))) {
      printf("Failed to bind socket \n");
      retVal = false;
    }
  }

  if (retVal) {
    struct ip_mreq_source cmd;
    InetPton(AF_INET, GetRxIpAddr().c_str(), &cmd.imr_multiaddr.s_addr);
    cmd.imr_sourceaddr.s_addr = htonl(INADDR_ANY);
    InetPton(AF_INET, _interface.c_str(), &cmd.imr_interface.s_addr);
    if (-1 == cmd.imr_multiaddr.s_addr) {
      printf("IP[%s] is not a multicast address \n", GetRxIpAddr().c_str());
      retVal = false;
    }
    if (retVal) {
      if (0 > setsockopt(_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&cmd,
                         sizeof(cmd))) {
        printf("Failed to join mulitcast group \n");
        retVal = false;
      }
    }
  }
  return retVal;
}
