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
 * @file HwInstIfc.h
 *
 * @brief Defines the hardware property.
 *
 */
#ifndef COM_COMMON_OSAL_WINDOWS_HW_IFC_H
#define COM_COMMON_OSAL_WINDOWS_HW_IFC_H

#include <HwInventory.h>
#include <HwProperty.h>
#include <OSALIface.h>

namespace osal {

/*
 * Hardware interface for can, rs485 and ethernet devices.
 */
class HwInstIfc {
public:
  /* constructor */
  HwInstIfc() {}

  /* destructor */
  virtual ~HwInstIfc() {}

  /**
   * @brief Initializes the device.
   *
   * @param  [in]     hwProperty  device configuration.
   *
   * @returns True if successful, false if failed.
   */
  virtual bool Init(IN std::shared_ptr<HwProperty> hwProperty) = 0;

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
   * @returns True if successful, false if failed.
   */
  virtual bool RegisterCallback(IN const osal::types::HwRegistry &registry,
                                IN ReceiverCallback callback) = 0;

  /**
   * @brief Unregister a receiver callback.
   *
   * Unregister a receiver callback function for the given hardware device.
   *
   * @param  [in]     registry  hardware description.
   *
   * @returns True if successful, false if failed.
   */
  virtual bool
  UnRegisterReceiver(IN const osal::types::HwRegistry &registry) = 0;

  /**
   * @brief Streams a data buffer.
   *
   * Streams a data buffer over the given hardware device.
   *
   * @param  [in]     registry  hardware desciption.
   *
   * @param  [in]     buffer    data buffer.
   *
   * @returns True if successful, false if failed.
   */
  virtual bool SendData(IN const osal::types::HwRegistry &registry,
                        IN const osal::types::BufferDescriptor &buffer) = 0;
};

} // namespace osal

#endif
