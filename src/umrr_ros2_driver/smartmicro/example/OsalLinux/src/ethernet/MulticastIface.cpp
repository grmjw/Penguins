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
#include <ethernet/MulticastIface.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

const size_t MAX_BUFF_SIZE = 65535U;
const uint32_t TERMINATION_MULTI_RECEIVER_CNT = 200U;

osal::MulticastIface::MulticastIface(const std::string &ifaceName,
                                     const std::string &ip, uint32_t port)
    : EthIface(ifaceName, ip, port),
      _socket(-1),
      _isRun(false),
      _buffer(new uint8_t[MAX_BUFF_SIZE]) {}

osal::MulticastIface::~MulticastIface() {
  Stop();
  struct ip_mreq cmd;
  // drop membership
  cmd.imr_multiaddr.s_addr = inet_addr(GetRxIpAddr().c_str());
  cmd.imr_interface.s_addr = inet_addr(_interface_ip.c_str());
  if (0 >
      setsockopt(_socket, IPPROTO_IP, IP_DROP_MEMBERSHIP, &cmd, sizeof(cmd))) {
    printf("Error: Failed to drop mulitcast option \n");
  }
  close(_socket);
  delete[] _buffer;
}

bool osal::MulticastIface::Init() {
  bool retVal = getIfaceIp();
  if (retVal) {
    retVal = joinGrp();
  } else {
    printf("Error: Failed to get interface ip address \n");
  }
  return retVal;
}

bool osal::MulticastIface::Start() {
  _isRun.store(true);
  _isStopped.store(false);
  _thread = std::thread(&MulticastIface::receiver, this);
  _thread.detach();

  return true;
}

void osal::MulticastIface::Stop() {
  _isRun.store(false);
  // Wait for termination of receiver()-Thread
  uint32_t timeCnt = 0;
  while (!_isStopped.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(12));
    timeCnt++;
    if (timeCnt > TERMINATION_MULTI_RECEIVER_CNT) {
      printf(
          "MulticastIface::Stop(): No termination response from "
          "receiver()-Thread\n");
      break;
    }
  }
}

bool osal::MulticastIface::RegisterReceiver(IN const std::string &ip,
                                            IN ReceiverCallback callback) {
  _callback = callback;
  return true;
}

bool osal::MulticastIface::UnRegisterReceiver(IN const std::string &ip) {
  _callback = nullptr;
  return true;
}

void osal::MulticastIface::receiver() {
  while (_isRun.load()) {
    sockaddr_in src;
    socklen_t srcLen = sizeof(src);
    // receive from the socket
    auto received =
        recvfrom(_socket, _buffer, MAX_BUFF_SIZE, 0,
                 reinterpret_cast<struct sockaddr *>(&src), &srcLen);
    if (0 < received) {
      if (_callback) {
        osal::types::BufferDescriptor desc(_buffer, received);
        // call the stored callback
        _callback(desc);
      }
    }
  }
  _isStopped.store(true);
}

bool osal::MulticastIface::SendData(IN const std::string &, IN uint16_t,
                                    IN osal::types::BufferDescriptor desc) {
  bool retVal = true;
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(GetRxIpAddr().c_str());
  addr.sin_port = htons(GetRxPort());
  auto sent = sendto(_socket, desc.GetBufferPtr(), desc.GetSize(), 0,
                     (struct sockaddr *)&addr, sizeof(addr));
  if (sent != desc.GetSize()) {
    printf("Error: Only [%zu] bytes were sent \n", sent);
    retVal = false;
  }

  return retVal;
}

bool osal::MulticastIface::joinGrp() {
  struct sockaddr_in addr;
  bool retVal = true;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(GetRxIpAddr().c_str());
  addr.sin_port = htons(_port);
  _socket = socket(PF_INET, SOCK_DGRAM, 0);
  if (0 > _socket) {
    printf("Error: Failed to create a socket \n");
    retVal = false;
  }
  if (retVal) {
    int value = 1;
    if (0 >
        setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value))) {
      printf("Error: Failed to set reuse option \n");
      retVal = false;
    }
  }
  if (retVal) {
    // Set timeout-Option for socket with timeval = 100 msec
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;  // 100 msex = 100000 usec
    if (0 > setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv))) {
      printf(
          "Error in osal::MulticastIface: Failed to set timeout option for "
          "socket\n");
      retVal = false;
    }
  }
  if (retVal) {
    if (0 > bind(_socket, (struct sockaddr *)&addr, sizeof(addr))) {
      printf("Error: Failed to bind socket \n");
      retVal = false;
    }
  }
  if (retVal) {
    int value = 0;
    if (0 > setsockopt(_socket, IPPROTO_IP, IP_MULTICAST_LOOP, &value,
                       sizeof(value))) {
      printf("Error: Failed to set mulitcast option \n");
      retVal = false;
    }
  }
  if (retVal) {
    struct in_addr out_addr;
    out_addr.s_addr = inet_addr(_interface_ip.c_str());
    int status = setsockopt(_socket, IPPROTO_IP, IP_MULTICAST_IF,
                            (char *)&out_addr, sizeof(out_addr));
    if (0 > status) {
      printf("Error: Failed to set multicast interface [%i] \n", status);
      retVal = false;
    }
  }

  if (retVal) {
    struct ip_mreq cmd;
    cmd.imr_multiaddr.s_addr = inet_addr(GetRxIpAddr().c_str());
    cmd.imr_interface.s_addr = inet_addr(_interface_ip.c_str());
    if (-1 == cmd.imr_multiaddr.s_addr) {
      printf("Error: IP[%s] is not a multicast address \n",
             GetRxIpAddr().c_str());
      retVal = false;
    }
    if (retVal) {
      int status =
          setsockopt(_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &cmd, sizeof(cmd));
      if (0 > status) {
        printf("Error: Failed to join mulitcast group [%i] \n", status);
        retVal = false;
      }
    }
  }
  return retVal;
}

bool osal::MulticastIface::getIfaceIp() {
  bool retVal = false;
  struct ifaddrs *ifAddrs;
  // Get all linux ethernet interfaces
  if (-1 == getifaddrs(&ifAddrs)) {
    printf("Error in osal::MulticastIface: Failed to retreive ip address\n");
    return retVal;
  } else {
    // Search for required ethernet interface
    for (auto iface = ifAddrs; iface != NULL; iface = iface->ifa_next) {
      if (iface->ifa_addr == NULL) {
        continue;
      }
      char host[NI_MAXHOST];
      auto family = iface->ifa_addr->sa_family;
      if (family == AF_INET) {
        if (0 != getnameinfo(iface->ifa_addr, sizeof(struct sockaddr_in), host,
                             NI_MAXHOST, NULL, 0, NI_NUMERICHOST)) {
          continue;
        }
      } else {
        continue;
      }
      // Compare found ethernet interface from list with configured EthIface
      // from registry
      if (0 == _ifaceName.compare(iface->ifa_name)) {
        // Set the rx ip address
        _interface_ip = std::string(host);
        retVal = true;
        break;
      }
    }
  }
  freeifaddrs(ifAddrs);
  return retVal;
}
