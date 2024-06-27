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

#ifndef ETHERNET__UDPIFACE_H_
#define ETHERNET__UDPIFACE_H_

#include <ethernet/UnicastIface.h>
#include <netinet/ip.h>

#include <string>

namespace osal {
class UdpIface : public UnicastIface {
 public:
  UdpIface(const std::string &, uint16_t port);
  virtual ~UdpIface();

 protected:
  virtual bool init();

  virtual void receiver();
  virtual bool createSocket(IN const std::string &ip, IN uint16_t port,
                            OUT int &result);
  virtual bool send(IN int socket, IN const std::string &ip, IN uint16_t port,
                    IN osal::types::BufferDescriptor &desc);

 private:
  bool createSocketAddr(IN const std::string &ip, IN uint16_t port,
                        OUT sockaddr_in &addr);

  uint8_t *_buffer;
};

}  // namespace osal

#endif  // ETHERNET__UDPIFACE_H_
