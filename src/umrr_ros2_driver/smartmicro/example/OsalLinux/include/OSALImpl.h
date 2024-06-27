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
 * @file OSALImpl.h
 *
 * @brief Defines the osal upper layer and used the osal interface.
 *
 */
#ifndef OSALIMPL_H_
#define OSALIMPL_H_

#include <HwInventory.h>
#include <OSALIface.h>

#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>

namespace osal {
// forwaded declarations
class CanIface;
class Rs485Iface;
class MulticastIface;
class UdpIface;

/**
 * This class contains the interface function for the osal layer.
 *
 */
class OSALImpl : public OSALIface {
 public:
  /* constructor */
  OSALImpl();
  /* destructor */
  virtual ~OSALImpl();
  /**
   * @brief Initialize the osal layer.
   *
   * Parse the config file and initializes the can, rs485 and ethernet devices.
   *
   * @param  [in]     configPath  path to the osal configuration file.
   *
   * @returns True if successful, false if failed.
   */

  virtual bool Init(const std::string &configPath);
  /**
   * @brief Describes the hardware interfaces.
   *
   * Returns a list with the hardware interface and those configuration.
   *
   * @param  [out]    hwDescriptor  a list with the hardware interfaces.
   *
   * @returns True if successful, false if failed.
   */
  virtual bool GetHwIfaces(
      OUT std::list<std::shared_ptr<osal::types::HwIfaceDescriptor>>
          &hwDescriptor);
  /**
   * @brief Register a receiver callback.
   *
   * Registers a receiver callback function for the given hardware device,
   * which schould be called, when a new buffer arrives.
   *
   * @param  [in]     registry  hardware description.
   *
   * @param  [in]     callback  callback function which should be called
   *                            upon a reception of a package.
   *
   * @returns @ref ErrorCode
   */

  virtual osal::types::ErrorCode RegisterReceiver(
      IN const osal::types::HwRegistry &registry, IN ReceiverCallback callback);
  /**
   * @brief Unregister a receiver callback.
   *
   * Unregister a receiver callback function for the given hardware device.
   *
   * @param  [in]     registry  hardware description.
   *
   * @returns @ref ErrorCode
   */
  virtual osal::types::ErrorCode UnRegisterReceiver(
      IN const osal::types::HwRegistry &registry);
  /**
   * @brief Streams a data buffer.
   *
   * Streams a data buffer over the given hardware device.
   *
   * @param  [in]     registry  hardware description.
   *
   * @param  [in]     buffer    data buffer.
   *
   * @returns @ref ErrorCode
   */

  virtual osal::types::ErrorCode SendData(
      IN const osal::types::HwRegistry &registry,
      IN const osal::types::BufferDescriptor &buffer);

 private:
  // CAN Interface
  osal::types::ErrorCode registerCanReceiver(
      IN const std::set<osal::types::CanId> &canIdset,
      IN osal::types::CanDevId canDeviceId, IN ReceiverCallback);

  osal::types::ErrorCode unregisterCanReceiver(
      IN const std::set<osal::types::CanId> &canIdset,
      IN osal::types::CanDevId canDeviceId);

  osal::types::ErrorCode sendCanMsg(IN osal::types::CanDevId canDeviceId,
                                    IN const osal::types::BufferDescriptor &);

  // Ethernet-Interface
  osal::types::ErrorCode registerEthernetReceiver(
      IN const std::string &ip, IN osal::types::EthTransportType protoType,
      IN uint32_t port, IN ReceiverCallback);

  osal::types::ErrorCode unegisterEthernetReceiver(
      IN const std::string &ip, IN osal::types::EthTransportType protoType,
      IN uint32_t port);

  osal::types::ErrorCode sendEthMsg(IN const std::string &ip,
                                    IN osal::types::EthTransportType,
                                    IN uint32_t port,
                                    IN const osal::types::BufferDescriptor &);

  // RS485-Interface
  osal::types::ErrorCode registerRS485Receiver(
      IN osal::types::SerialDevId deviceId, IN ReceiverCallback);

  osal::types::ErrorCode unregisterRS485Receiver(
      IN osal::types::SerialDevId deviceId);

  osal::types::ErrorCode sendRS485Msg(IN osal::types::SerialDevId deviceId,
                                      IN const osal::types::BufferDescriptor &);

  bool createCanIface(IN std::shared_ptr<osal::types::HwCanDescriptor> desc);
  bool createRs485Iface(
      IN std::shared_ptr<osal::types::HwRS485Descriptor> desc);
  bool createUdpIface(
      IN std::shared_ptr<osal::types::HwEthernetDescriptor> desc);

  // Receiver Callback Maps
  typedef std::map<osal::types::CanDevId, std::unique_ptr<CanIface>>
      CanIfaceMap;
  typedef std::map<osal::types::SerialDevId, std::unique_ptr<Rs485Iface>>
      Rs485IfaceMap;
  typedef std::pair<std::string, uint16_t> EthIfaceKey;
  typedef std::map<EthIfaceKey, std::shared_ptr<MulticastIface>>
      MulticastIfaceMap;
  typedef std::list<std::shared_ptr<osal::types::HwIfaceDescriptor>> IfaceList;

  CanIfaceMap _canIfaceMap;
  Rs485IfaceMap _rs485IfaceMap;
  MulticastIfaceMap _multicastMap;
  std::shared_ptr<UdpIface> _udpIface;

  // OSAL utilities
  std::shared_ptr<HwInventory> _hwInventory;
  IfaceList _hwIfList;
  std::string _configPath;
};
}  // namespace osal

#endif  // OSALIMPL_H_
