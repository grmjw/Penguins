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

#ifndef COM_COMMON_OSAL_WINDOWS_UDP_IFACE_H
#define COM_COMMON_OSAL_WINDOWS_UDP_IFACE_H

#include <UnicastIface.h>
#include <winsock2.h>

namespace osal {

class UdpIface : public UnicastIface {
public:
  UdpIface(const std::string &, uint32_t port);

  virtual ~UdpIface();

protected:
  virtual bool init();

  virtual void receiver();

  virtual bool createSocket(IN const std::string &ip, IN uint16_t port,
                            OUT SOCKET &result);

  virtual bool send(IN SOCKET socket, IN const std::string &ip,
                    IN uint16_t port, IN osal::types::BufferDescriptor &desc);

private:
  char *_buffer;
};

} // namespace osal

#endif
