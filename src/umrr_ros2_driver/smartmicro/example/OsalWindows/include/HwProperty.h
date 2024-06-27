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
 * @file HwProperty.h
 *
 * @brief Defines the hardware property.
 *
 */
#ifndef COM_COMMON_OSAL_WINDOWS_HW_PROP_H
#define COM_COMMON_OSAL_WINDOWS_HW_PROP_H

#include <OSALIface.h>
#include <iterator>
#include <list>
#include <map>
#include <string>

#include <sys/stat.h>

namespace osal {

/**
 * This class descibres a hardware device and can be used for the can,
 * rs485 and ethernet interfaces.
 *
 */
class HwProperty {
public:
  /**
   * @brief Initialize the hardware property with the given interface type.
   *
   * @param  [in] hwType     @ref HwIfaceType hardware interface type.
   */
  HwProperty(osal::types::HwIfaceType hwType);

  /* destructpr */
  virtual ~HwProperty();

  /**
   * @brief Returns hardware interface type.
   *
   * @returns @ref HwIfaceType returns hardware interface .
   */
  osal::types::HwIfaceType GetHwIfaceType() const;

  /**
   * @brief Returns hardware interface name.
   *
   * @returns returns hardware interface name.
   */
  std::string GetIfaceName() const;

  /**
   * @brief Returns device supplier.
   *
   * @returns returns device supplier.
   */
  std::string GetDevSupplier() const;

  /**
   * @brief Returns device type.
   *
   * @returns returns device type.
   */
  std::string GetDevType() const;

  /**
   * @brief Returns link speed.
   *
   * @returns returns link speed.
   */
  std::string GetLinkSpeed() const;

  /**
   * @brief Returns ip address.
   *
   * @returns returns ip address.
   */
  std::string GetIpAddress() const;

  /**
   * @brief Returns used port.
   *
   * The used port can describes the com port for rs485
   * or the ip port from ethernet.
   *
   * @returns returns ip address.
   */
  std::string GetUsedPort() const;

  /**
   * @brief Returns device id.
   *
   * @returns returns device id.
   */
  std::string GetDeviceId() const;

  /**
   * @brief Sets interface name.
   *
   * @param  [in] ifcName     interface name.
   */
  void SetIfaceName(IN std::string ifcName);

  /**
   * @brief Sets device supplier.
   *
   * @param  [in] hwDevSupplier     device supplier.
   */
  void SetDevSupplier(IN std::string hwDevSupplier);

  /**
   * @brief Sets device type.
   *
   * @param  [in] hwDevType     device type.
   */
  void SetDevType(IN std::string hwDevType);

  /**
   * @brief Sets link speed.
   *
   * @param  [in] linkSpeed     link speed.
   */
  void SetLinkSpeed(IN std::string linkSpeed);

  /**
   * @brief Sets ip address.
   *
   * @param  [in] ipAddress     ip address.
   */
  void SetIpAddress(IN std::string ipAddress);

  /**
   * @brief Sets used port.
   *
   * @param  [in] usedPort     used port from rs485 or ehternet.
   */
  void SetUsedPort(IN std::string usedPort);

  /**
   * @brief Sets device id.
   *
   * @param  [in] deviceId     device id.
   */
  void SetDeviceId(IN std::string deviceId);

private:
  osal::types::HwIfaceType _hwType;
  std::string _ifcName;
  std::string _hwDevSupplier;
  std::string _hwDevType;
  std::string _linkSpeed;
  std::string _ipAddress;
  std::string _usedPort;
  std::string _deviceId;
};

} // namespace osal

#endif
