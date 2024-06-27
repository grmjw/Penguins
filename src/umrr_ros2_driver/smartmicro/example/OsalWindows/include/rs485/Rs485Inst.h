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
 * @file Rs485Inst.h
 *
 * @brief Rs485 device implementation.
 *
 */
#ifndef COM_COMMON_OSAL_WINDOWS_RS485_INST_H
#define COM_COMMON_OSAL_WINDOWS_RS485_INST_H

#include <HwInstIfc.h>
#include <HwProperty.h>
#include <OSALIface.h>
#include <OSALTypes.h>
#define _WINSOCKAPI_ // stops windows.h including winsock.h
#include <Windows.h>
#include <iostream>
#include <mutex>
#include <thread>

namespace osal {

/*
 * The class describes the rs485 device and used the hardware instanz
 * interface.
 */
class Rs485Inst : public HwInstIfc {
public:
  /* constructor */
  Rs485Inst();

  /* destructor */
  ~Rs485Inst();

  /**
   * @brief Initializes the device.
   *
   * This function requiers a com port (usedPort) and baudrate
   * (linkSpeed) to initializes the device.
   *
   * @param  [in]     hwProperty  device configuration.
   *
   * @returns True if successful, false if failed.
   */
  bool Init(IN std::shared_ptr<HwProperty> hwProperty);

  /**
   * @brief Register a receiver callback.
   *
   * Registers a receiver callback function for the given hardware device,
   * which schould be called, when a new buffer arrives. Only one callback
   * can be registered
   *
   * @param  [in]     registry  hardware description.
   *
   * @param  [in]     callback  callback function which should be called
   *                            upon a reception of a package.
   *
   * @returns True if successful, false if failed.
   */
  bool RegisterCallback(IN const osal::types::HwRegistry &registry,
                        IN ReceiverCallback);

  /**
   * @brief Unregister a receiver callback.
   *
   * Unregister a receiver callback function for the given hardware device.
   *
   * @param  [in]     registry  hardware description.
   *
   * @returns True if successful, false if failed.
   */
  bool UnRegisterReceiver(IN const osal::types::HwRegistry &registry);

  /**
   * @brief Streams a data buffer.
   *
   * Streams a data buffer over the given hardware device.
   *
   * @param  [in]     registry  hardware description.
   *
   * @param  [in]     bufferDesc    data buffer.
   *
   * @returns True if successful, false if failed.
   */
  bool SendData(IN const osal::types::HwRegistry &registry,
                IN const osal::types::BufferDescriptor &bufferDesc);

private:
  /**
   * @brief Receiver thread.
   *
   * This function is a receive thread.
   *
   */
  void receiver();

  /**
   * @brief Configure the baudrate from the hardware device.
   *
   */
  bool configureBaudrate();

  std::shared_ptr<HwProperty> _hwProperty;
  HANDLE _uartPortHandle;
  std::thread _thread;
  std::mutex _mutex;
  ReceiverCallback _callback;

  bool _processThread;
  uint8_t *_rxBuffer;
};

} // namespace osal

#endif
