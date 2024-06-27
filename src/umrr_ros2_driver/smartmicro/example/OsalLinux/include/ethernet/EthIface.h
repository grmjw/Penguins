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
/**
 * @addtogroup osal
 * @{
 *
 * @file EthIface.h
 *
 * @brief Base class for all eth inetrfaces
 *
 */

#ifndef ETHERNET__ETHIFACE_H_
#define ETHERNET__ETHIFACE_H_

#include <OSALIface.h>
#include <OSALTypes.h>
#include <termios.h>

#include <iostream>
#include <mutex>
#include <string>
#include <thread>

namespace osal {
class EthIface {
 public:
  /* consturctors */
  EthIface() : _port(0) {}
  EthIface(const std::string &ifaceName, const std::string &ip, uint16_t port)
      : _ifaceName(ifaceName), _ip(ip), _port(port) {}
  /* destructor */
  virtual ~EthIface() {}
  /**
   * @brief Initialize eth interface.
   * @returns True if successful, false if failed.
   */
  virtual bool Init() = 0;
  /**
   * @brief Starts eth interface thread.
   * @returns True if successful, false if failed.
   */
  virtual bool Start() = 0;
  /**
   * @brief Stops eth interface thread.
   */
  virtual void Stop() = 0;

  /**
   * @brief Register a receiver callback.
   *
   *
   * @param  [in]     ip  ip address of the sender
   *
   * @param  [in]     callback  callback function which should be called
   *                            upon a reception of a package.
   *
   * @returns True if successful, false if failed.
   */
  virtual bool RegisterReceiver(IN const std::string &ip,
                                IN ReceiverCallback callback) = 0;

  /**
   * @brief Unregister a receiver callback.
   *
   *
   * @param  [in]     ip  ip address of the sender.
   *
   * @returns True if successful, false if failed.
   */
  virtual bool UnRegisterReceiver(IN const std::string &) = 0;

  /**
   * @brief Returns ip address of the receiving socket.
   * @returns Returns ip address of receiving socket as string.
   */
  inline std::string GetRxIpAddr() const { return _ip; }
  /**
   * @brief Set ip address of the receiving socket.
   *
   *
   * @param  [in]     ip  ip address
   *
   * @returns void
   */
  inline void SetRxIpAddr(IN const std::string &ip) { _ip = ip; }

  /**
   * @brief Returns ethernet interface name etc. eth0.
   * @returns Returns ethernet interface name
   */
  inline std::string GetIfaceName() const { return _ifaceName; }
  /**
   * @brief Set ethernet interface name etc. eth0.
   *
   * @param  [in]  ifaceName ethernet interface name.
   *
   * @returns void
   */
  inline void SetIfaceName(IN const std::string &ifaceName) {
    _ifaceName = ifaceName;
  }

  /**
   * @brief Returns TCP/UDP port.
   * @returns Returns TCP/UDP port.
   */
  inline uint16_t GetRxPort() const { return _port; }

  /**
   * @brief Set TCP/UDP port of the receiving socket.
   *
   *
   * @param  [in]     ip  ip address
   *
   * @returns void
   */
  inline void SetRxPort(IN uint16_t port) { _port = port; }

  /**
   * @brief Streams a data buffer.
   *
   * Streams a data buffer over the given ip address.
   *
   * @param  [in]     ip        ip address.
   *
   * @param  [in]     port      TCP/UDP port.
   *
   * @param  [in]     buffer    data buffer.
   *
   * @returns True if successful, false if failed.
   */
  virtual bool SendData(IN const std::string &ip, IN uint16_t port,
                        IN osal::types::BufferDescriptor desc) = 0;

 protected:
  std::string _ifaceName;
  std::string _ip;
  uint16_t _port;
};

}  // namespace osal

#endif  // ETHERNET__ETHIFACE_H_
