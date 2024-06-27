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

#ifndef COM_COMMON_OSAL_WINDOWS_MULTICAST_IFACE_H
#define COM_COMMON_OSAL_WINDOWS_MULTICAST_IFACE_H

#include <EthIface.h>
#include <winsock2.h>

namespace osal {

class MulticastIface : public EthIface {
public:
  MulticastIface(const std::string &ip, uint32_t port,
                 const std::string &ethInterface);
  virtual ~MulticastIface();

  virtual bool Init();

  virtual bool Start();

  virtual void Stop();

  virtual bool RegisterReceiver(IN const std::string &, IN ReceiverCallback);

  virtual bool UnRegisterReceiver(IN const std::string &);

  virtual bool SendData(IN const std::string &ip, IN uint16_t port,
                        IN osal::types::BufferDescriptor desc);

private:
  bool joinGrp();

  void receiver();

  SOCKET _socket;
  char *_buffer;
  ReceiverCallback _callback;
  bool _isRun;
  std::thread _thread;
  std::string _interface;
};

} // namespace osal

#endif
