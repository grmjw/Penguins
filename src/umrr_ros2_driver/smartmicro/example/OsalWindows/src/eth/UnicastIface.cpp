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

#include <UnicastIface.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace osal::types;
using namespace osal;

UnicastIface::UnicastIface(const std::string &ipAddress, uint16_t port)
    : EthIface(ipAddress, port), _socket(-1), _isRun(false) {}

bool UnicastIface::Init() {
  bool retVal = false;
  retVal = init();
  return retVal;
}

bool UnicastIface::RegisterReceiver(IN const std::string &ip,
                                    IN ReceiverCallback callback) {
  bool retVal = false;
  std::lock_guard<std::mutex> lock(_mutex);
  auto it = _callbacks.find(ip);
  if (it == _callbacks.end()) {
    _callbacks.insert(std::pair<std::string, ReceiverCallback>(ip, callback));
    retVal = true;
  }
  return retVal;
}

bool UnicastIface::UnRegisterReceiver(IN const std::string &ip) {
  bool retVal = false;
  std::lock_guard<std::mutex> lock(_mutex);
  auto it = _callbacks.find(ip);
  if (it != _callbacks.end()) {
    _callbacks.erase(it);
    retVal = true;
  }
  return retVal;
}

bool UnicastIface::Start() {
  _isRun = true;
  _thread = std::thread(&UnicastIface::receiver, this);
  _thread.detach();
  return true;
}

void UnicastIface::Stop() { _isRun = false; }

bool UnicastIface::getCallback(IN const std::string &ip,
                               OUT ReceiverCallback &callback) {
  bool retVal = false;
  std::lock_guard<std::mutex> lock(_mutex);
  auto it = _callbacks.find(ip);
  if (it != _callbacks.end()) {
    callback = it->second;
    retVal = true;
  }
  return retVal;
}

bool UnicastIface::SendData(IN const std::string &ip, IN uint16_t port,
                            IN BufferDescriptor desc) {
  bool retVal = true;

  SOCKADDR_IN addr;
  addr.sin_family = AF_INET;
  InetPton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr);
  addr.sin_port = htons(port);

  int sent = sendto(_socket, reinterpret_cast<char *>(desc.GetBufferPtr()),
                    static_cast<int>(desc.GetSize()), 0, (sockaddr *)&addr,
                    sizeof(addr));
  if (sent == SOCKET_ERROR) {
    printf("socket can not sending: %i \n", WSAGetLastError());
    retVal = false;
  }
  return retVal;
}
