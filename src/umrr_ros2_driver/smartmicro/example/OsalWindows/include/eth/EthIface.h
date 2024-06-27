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

#ifndef COM_COMMON_OSAL_WINDOWS_ETH_IFACE_H
#define COM_COMMON_OSAL_WINDOWS_ETH_IFACE_H

#include <OSALIface.h>
#include <OSALTypes.h>
#include <iostream>
#include <mutex>
#include <thread>

namespace osal {

class EthIface {
public:
  EthIface() : _port(0) {}
  EthIface(const std::string &ip, uint16_t port) : _ip(ip), _port(port) {}
  virtual ~EthIface() {}

  virtual bool Init() = 0;

  virtual bool Start() = 0;

  virtual void Stop() = 0;

  virtual bool RegisterReceiver(IN const std::string &,
                                IN ReceiverCallback) = 0;

  virtual bool UnRegisterReceiver(IN const std::string &) = 0;

  inline std::string GetRxIpAddr() const { return _ip; }

  inline void SetRxIpAddr(IN const std::string &ip) { _ip = ip; }

  inline uint16_t GetRxPort() const { return _port; }

  inline void GetRxPort(IN uint16_t port) { _port = port; }

  virtual bool SendData(IN const std::string &ip, IN uint16_t port,
                        IN osal::types::BufferDescriptor desc) = 0;

protected:
  std::string _ip;
  uint16_t _port;
};

} // namespace osal

#endif
