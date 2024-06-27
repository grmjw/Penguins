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
 * @file Rs485Iface.h
 *
 * @brief Rs485 device implementation.
 *
 */
#ifndef RS485__RS485IFACE_H_
#define RS485__RS485IFACE_H_

#include <OSALIface.h>
#include <OSALTypes.h>
#include <termios.h>

#include <atomic>
#include <iostream>
#include <string>
#include <thread>

namespace osal {
/*
 * The class describes the rs485 device and used the hardware instanz
 * interface.
 */
class Rs485Iface {
 public:
  /* constructor */
  Rs485Iface(const std::string &, uint32_t);

  /* destructor */
  virtual ~Rs485Iface();

  /**
   * @brief Initializes the device.
   *
   *
   * @returns True if successful, false if failed.
   */
  bool Init();

  /**
   * @brief Start to listen the serial socket.
   *
   * @returns True if successful, false if failed.
   */
  bool Start();

  /**
   * @brief Stop listening the serial socket.
   *
   * @returns No return.
   */
  void Stop();

  /**
   * @brief Register a receiver callback.
   *
   * Registers a receiver callback function for the given RS485 device,
   * only one callbacl is allowed
   *
   * @param  [in]     callback  callback function which should be called
   *                            upon a reception of a package.
   *
   * @returns True if successful, false if failed.
   */
  void RegisterReceiver(IN ReceiverCallback);

  /**
   * @brief Unregister a receiver callback.
   *
   * Unregisters a receiver callback function for the given RS485 device,
   *
   * @param  [in]     canIds  list of can ids.
   *
   * @returns True if successful, false if failed.
   */
  void UnRegisterReceiver();

  /**
   * @brief Streams a data buffer.
   *
   * Streams a data buffer over the given CAN device.
   *
   * @param  [in]     bufferDesc    data buffer.
   *
   * @returns True if successful, false if failed.
   */
  bool SendMsg(IN const osal::types::BufferDescriptor &bufferDesc);

 private:
  void receiver();
  bool getBaudrateFlag(OUT speed_t &flag);
  bool rcvMsg(uint8_t *buffer, size_t size);

  std::string _ifaceName;
  int32_t _fd;
  std::thread _thread;
  ReceiverCallback _callback;
  std::atomic_bool _isRun;
  std::atomic_bool _isStopped;
  uint32_t _baudrate;
};

}  // namespace osal

#endif  // RS485__RS485IFACE_H_
