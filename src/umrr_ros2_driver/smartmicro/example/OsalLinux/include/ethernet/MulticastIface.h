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

#ifndef ETHERNET__MULTICASTIFACE_H_
#define ETHERNET__MULTICASTIFACE_H_

#include <ethernet/EthIface.h>
#include <netinet/ip.h>

#include <atomic>
#include <string>

namespace osal {

class MulticastIface : public EthIface {
 public:
  MulticastIface(const std::string &ifaceName, const std::string &ip,
                 uint32_t port);
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

  bool getIfaceIp();

  int _socket;
  uint8_t *_buffer;
  ReceiverCallback _callback;
  std::atomic_bool _isRun;
  std::atomic_bool _isStopped;
  std::thread _thread;
  std::string _interface_ip;
};

}  // namespace osal

#endif  // ETHERNET__MULTICASTIFACE_H_
