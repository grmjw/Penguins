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
#ifndef COM_COMMON_OSAL_WINDOWS_IMPL_H
#define COM_COMMON_OSAL_WINDOWS_IMPL_H

#include <EthIface.h>
#include <HwInstIfc.h>
#include <HwInventory.h>
#include <HwProperty.h>
#include <MulticastIface.h>
#include <OSALIface.h>
#include <Rs485Inst.h>
#include <UdpIface.h>
#include <map>
#include <memory>
#include <vector>

namespace osal {

/**
 * This class contains the interface function for the osal layer.
 *
 */
class OSALImpl : public OSALIface {
public:
  /* constructor */
  OSALImpl();

  /* destructor */
  ~OSALImpl();

  /**
   * @brief Initialize the osal layer.
   *
   * Parse the config file and initializes the can, rs485 and ethernet devices.
   *
   * @param  [in]     configPath  path to the osal configuration file.
   *
   * @returns True if successful, false if failed.
   */
  bool Init(IN const std::string &configPath);

  /**
   * @brief Describes the hardware interfaces.
   *
   * Returns a list with the hardware interface and those configuration.
   *
   * @param  [out]    hwDescriptor  a list with the hardware interfaces.
   *
   * @returns True if successful, false if failed.
   */
  bool
  GetHwIfaces(OUT std::list<std::shared_ptr<osal::types::HwIfaceDescriptor>>
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
  osal::types::ErrorCode
  RegisterReceiver(IN const osal::types::HwRegistry &registry,
                   IN ReceiverCallback callback);

  /**
   * @brief Unregister a receiver callback.
   *
   * Unregister a receiver callback function for the given hardware device.
   *
   * @param  [in]     registry  hardware description.
   *
   * @returns @ref ErrorCode
   */
  osal::types::ErrorCode
  UnRegisterReceiver(IN const osal::types::HwRegistry &registry);

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
  osal::types::ErrorCode
  SendData(IN const osal::types::HwRegistry &registry,
           IN const osal::types::BufferDescriptor &buffer);

private:
  /* your own private part */
  bool createRs485Device(IN std::shared_ptr<HwProperty> desc);
  bool createEthDevice(IN std::shared_ptr<HwProperty> desc);

  typedef std::map<osal::types::SerialDevId, std::unique_ptr<Rs485Inst>>
      Rs485InstMap;
  typedef std::map<std::string, std::unique_ptr<UdpIface>> EthInstMap;
  typedef std::map<std::string, std::shared_ptr<MulticastIface>>
      MulticastIfaceMap;

  std::shared_ptr<HwInventory> _hwInventory;
  std::string _configPath;
  std::list<std::shared_ptr<HwProperty>> _hwPropList;
  Rs485InstMap _rs485InstMap;
  MulticastIfaceMap _multicastMap;
  std::shared_ptr<UdpIface> _ethInst;
};
} // namespace osal
#endif
