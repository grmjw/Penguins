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

#ifndef COM_COMMON_OSAL_WINDOWS_UNICAST_IFACE_H
#define COM_COMMON_OSAL_WINDOWS_UNICAST_IFACE_H

#include <EthIface.h>
#include <OSALIface.h>
#include <OSALTypes.h>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>
#include <winsock2.h>

namespace osal {

class UnicastIface : public EthIface {
public:
  UnicastIface(const std::string &ipAddress, uint16_t port);
  virtual ~UnicastIface() {}

  virtual bool Init();

  virtual bool Start();

  virtual void Stop();

  virtual bool RegisterReceiver(IN const std::string &ip,
                                IN ReceiverCallback callback);

  virtual bool UnRegisterReceiver(IN const std::string &ip);

  virtual bool SendData(IN const std::string &ip, IN uint16_t port,
                        IN osal::types::BufferDescriptor desc);

protected:
  virtual bool init() = 0;

  virtual void receiver() = 0;

  virtual bool createSocket(IN const std::string &ip, IN uint16_t port,
                            OUT SOCKET &result) = 0;

  virtual bool send(IN SOCKET socket, IN const std::string &ip,
                    IN uint16_t port,
                    IN osal::types::BufferDescriptor &desc) = 0;

  bool getCallback(IN const std::string &ip, OUT ReceiverCallback &);

  inline bool isRun() const { return _isRun; }

  SOCKET _socket;
  std::string _srcIpAddr;
  uint16_t _srcPort;

private:
  typedef std::map<std::string, SOCKET> SocketMap;
  typedef std::map<std::string, ReceiverCallback> CallbackMap;

  std::mutex _mutex;
  std::thread _thread;
  SocketMap _sockets;
  CallbackMap _callbacks;
  bool _isRun;
};

} // namespace osal
#endif
