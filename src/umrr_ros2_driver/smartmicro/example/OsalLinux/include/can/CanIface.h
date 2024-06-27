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
 * @file CanIface.h
 *
 * @brief CAN device implementation.
 *
 */
#ifndef CAN__CANIFACE_H_
#define CAN__CANIFACE_H_

#include <HwInventory.h>
#include <linux/can.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <sys/socket.h>

#include <atomic>
#include <cstring>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <thread>

const int32_t CAN_DATA_LEN_MAX = 8;

namespace osal {
class CanIface {
 public:
  /* constructor */
  CanIface(osal::types::CanDevId, const std::string &, uint32_t);
  /* destructor */
  virtual ~CanIface();

  /**
   * @brief Initializes the device.
   *
   * Open CAN socket to send/receive can messages. CAN interface
   * shall already exist(in ifconfig)
   *
   * @returns True if successful, false if failed.
   */
  bool Init();

  /**
   * @brief Start to listen the socket.
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
   * Registers a receiver callback function for the given CAN device,
   * which schould be called, when a new buffer arrives. Each set of can ids
   * has its own callback
   *
   * @param  [in]     canIds  list of can ids.
   *
   * @param  [in]     callback  callback function which should be called
   *                            upon a reception of a package.
   *
   * @returns True if successful, false if failed.
   */
  bool RegisterCanReceiver(IN const std::set<osal::types::CanId> &canIds,
                           IN ReceiverCallback callback);

  /**
   * @brief Unregister a receiver callback.
   *
   * Unregisters a receiver callback function for the given CAN device,
   *
   * @param  [in]     canIds  list of can ids.
   *
   * @returns True if successful, false if failed.
   */
  bool UnRegisterCanReceiver(IN const std::set<osal::types::CanId> &);

  /**
   * @brief Streams a data buffer.
   *
   * Streams a data buffer over the given CAN device.
   *
   * @param  [in]     bufferDesc    data buffer.
   *
   * @returns True if successful, false if failed.
   */
  bool SendCanMsg(IN const osal::types::BufferDescriptor &bufferDesc);

 private:
  void canReceiver();
  bool receiveCanMsg(OUT osal::types::CanId &, OUT osal::types::CanFormat &);

  int32_t _canFd;
  osal::types::CanDevId _canDeviceId;
  std::string _canIfaceName;
  std::thread _receiverThread;
  std::mutex _mutex;

  std::map<osal::types::CanId, ReceiverCallback> _canIdReceiverCallbackMap;

  std::string _canIfUp_cmd;
  std::string _canIfDown_cmd;
  std::string _canConfig_cmd;
  uint32_t _canBaudrate;
  std::atomic_bool _isRun;
  std::atomic_bool _isStopped;
};

}  // namespace osal

#endif  // CAN__CANIFACE_H_
