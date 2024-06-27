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

#include <UdpIface.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ws2tcpip.h>

using namespace osal::types;
using namespace osal;

const size_t MAX_UDP_SIZE = 4096U;

UdpIface::UdpIface(const std::string &ipAddress, uint32_t port)
    : UnicastIface(ipAddress, port), _buffer(new char[MAX_UDP_SIZE]) {
  printf("Create UDP rx socket on [%s] Port [%u] \n", ipAddress.c_str(), port);
}

osal::UdpIface::~UdpIface() {
  Stop();
  delete[] _buffer;
}

bool UdpIface::init() {
  bool retVal = true;
  // start winsock
  WSADATA data;
  WORD version = MAKEWORD(2, 2);
  int wsAccurateStart = WSAStartup(version, &data);
  if (wsAccurateStart != 0) {
    printf("Winsock not started \n");
    retVal = false;
  }
  _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (_socket == INVALID_SOCKET) {
    printf("Failed to create socket \n");
    retVal = false;
  }
  if (retVal) {
    // set recv timeout to 5 sec
    int timeout = 5000;
    setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(int));
    // set host addr
    SOCKADDR_IN hostAddr;
    hostAddr.sin_family = AF_INET;
    std::string ipAddr = GetRxIpAddr();
    InetPton(AF_INET, ipAddr.c_str(), &hostAddr.sin_addr.s_addr);
    hostAddr.sin_port = htons(GetRxPort());
    if (0 > bind(_socket, (struct sockaddr *)&hostAddr, sizeof(hostAddr))) {
      printf("Failed to bind socket \n");
      retVal = false;
    }
  }
  return retVal;
}

void UdpIface::receiver() {
  while (isRun()) {
    // zero buffer
    ZeroMemory(_buffer, MAX_UDP_SIZE);
    // recvfrom do receive on the bound socket.
    SOCKADDR_IN SenderAddr;
    int SenderAddrSize = sizeof(SenderAddr);
    int received = recvfrom(_socket, _buffer, MAX_UDP_SIZE, 0,
                            (sockaddr *)&SenderAddr, &SenderAddrSize);
    if (SOCKET_ERROR != received) {
      char tmp[16];
      inet_ntop(AF_INET, &SenderAddr.sin_addr, tmp, sizeof(tmp));

      std::string srcIp(tmp);
      _srcIpAddr = srcIp;
      _srcPort = ntohs(SenderAddr.sin_port);

      ReceiverCallback callback;
      if (getCallback(srcIp, callback)) {
        BufferDescriptor desc(reinterpret_cast<uint8_t *>(_buffer), received);
        callback(desc);
      }
    }
  }
}

bool UdpIface::createSocket(IN const std::string &ip, IN uint16_t port,
                            OUT SOCKET &result) {
  bool retVal = true;
  SOCKET soc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (0 > soc) {
    retVal = false;
  } else {
    result = soc;
  }
  return retVal;
}

bool UdpIface::send(IN SOCKET socket, IN const std::string &ip,
                    IN uint16_t port, IN BufferDescriptor &desc) {
  bool retVal = true;
  SOCKADDR_IN addr;
  addr.sin_family = AF_INET;
  InetPton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr);
  addr.sin_port = htons(port);

  int sent = sendto(socket, reinterpret_cast<char *>(desc.GetBufferPtr()),
                    static_cast<int>(desc.GetSize()), 0, (sockaddr *)&addr,
                    sizeof(addr));
  if (sent == SOCKET_ERROR) {
    printf("socket can not sending: %i ", WSAGetLastError());
    retVal = false;
  }
  return retVal;
}
