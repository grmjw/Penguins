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

#include <arpa/inet.h>
#include <ethernet/UdpIface.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

const size_t MAX_UDP_SIZE = 65535U;

osal::UdpIface::UdpIface(const std::string &ethIfaceName, uint16_t port)
    : UnicastIface(ethIfaceName, port), _buffer(new uint8_t[MAX_UDP_SIZE]) {}

osal::UdpIface::~UdpIface() {
  Stop();
  delete[] _buffer;
}

bool osal::UdpIface::init() {
  bool retVal = true;
  _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (0 > _socket) {
    printf("Error: Failed to create socket \n");
    retVal = false;
  }
  if (retVal) {
    // Set timeout-Option for socket with timeval = 100 msec
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;  // 100 msex = 100000 usec
    if (0 > setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv))) {
      printf(
          "Error in osal::UdpIface: Failed to set timeout option for socket\n");
      retVal = false;
    }
  }
  if (retVal) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(GetRxPort());
    inet_pton(AF_INET, GetRxIpAddr().c_str(), &addr.sin_addr.s_addr);
    if (0 > bind(_socket, (struct sockaddr *)&addr, sizeof(addr))) {
      printf("Failed to bind socket");
      retVal = false;
    }
  }
  return retVal;
}

void osal::UdpIface::receiver() {
  while (isRun()) {
    sockaddr_in src;
    socklen_t srcLen = sizeof(src);
    auto received =
        recvfrom(_socket, _buffer, MAX_UDP_SIZE, 0,
                 reinterpret_cast<struct sockaddr *>(&src), &srcLen);
    if (0 < received) {
      char tmp[16];
      inet_ntop(AF_INET, &src.sin_addr, tmp, sizeof(tmp));

      std::string srcIp(tmp);
      _srcIpAddr = srcIp;
      _srcPort = ntohs(src.sin_port);

      ReceiverCallback callback;
      if (getCallback(srcIp, callback)) {
        osal::types::BufferDescriptor desc(_buffer, received);
        callback(desc);
      }
    }
  }
  setIsStopped();
}

bool osal::UdpIface::createSocket(IN const std::string &ip, IN uint16_t port,
                                  OUT int &result) {
  bool retVal = true;
  int soc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (0 > soc) {
    retVal = false;
  } else {
    result = soc;
  }
  return retVal;
}

bool osal::UdpIface::createSocketAddr(IN const std::string &ip,
                                      IN uint16_t port, OUT sockaddr_in &addr) {
  bool retVal = false;
  if (1 == inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr)) {
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    retVal = true;
  }
  return retVal;
}

bool osal::UdpIface::send(IN int socket, IN const std::string &ip,
                          IN uint16_t port,
                          IN osal::types::BufferDescriptor &desc) {
  bool retVal = true;
  sockaddr_in addr;
  if (createSocketAddr(ip, port, addr)) {
    auto sent = sendto(socket, desc.GetBufferPtr(), desc.GetSize(), 0,
                       (struct sockaddr *)&addr, sizeof(addr));
    if (sent != desc.GetSize()) {
      printf("Error: Only [%zu] bytes were sent \n", sent);
      retVal = false;
    }

  } else {
    printf("Error: Failed to cretae socketaddr \n");
    retVal = false;
  }
  return retVal;
}
