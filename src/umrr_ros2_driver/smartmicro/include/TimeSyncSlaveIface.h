/**************************************************************************
Copyright (c) 2021, s.m.s, smart microwave sensors GmbH, Brunswick, Germany

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**************************************************************************/

#ifndef EXTERNAL__TIMESYNCSLAVEIFACE_H_
#define EXTERNAL__TIMESYNCSLAVEIFACE_H_

#include <ExternalTypes.h>
#include <VersionedIface.h>

#include <functional>
#include <memory>

namespace com {
namespace master {
typedef std::function<bool(uint64_t &)> GetSyncTimeCallback;
typedef std::function<bool(int64_t)> SetSyncOffsetCallback;

class EXPORT_SMART_ACCESS_LIB TimeSyncSlaveIface : public com::VersionedIface {
 public:
  /*
   * Function: Get()
   * Arguments: none
   * Return: std::shared_ptr<TimeSyncSlaveIface>
   * Description: Returns a singletone instance of a this class, since this is
   * only an abstract class, the instantiation should be done by a deriving
   * class.
   */
  static std::shared_ptr<TimeSyncSlaveIface> Get();

  /*
   * Function: RegisterGetSyncTimeCallback
   * Arguments:  GetSyncTimeCallback
   * Return: ErrorCode
   * Description: Register a callback to get slave time ,which will be
   * synchronized.
   */
  virtual com::types::ErrorCode RegisterGetSyncTimeCallback(
      IN GetSyncTimeCallback callback) = 0;

  /*
   * Function: RegisterSetSyncOffsetCallback
   * Arguments: SetSyncOffsetCallback
   * Return: ErrorCode
   * Description: Register a callback to set slaves offset to master
   */
  virtual com::types::ErrorCode RegisterSetSyncOffsetCallback(
      IN SetSyncOffsetCallback callback) = 0;

  /*
   * Function: SetSlaveId
   * Arguments: uint8_t slaveDevId slave device id[0..15]
   * Return: ErrorCode
   * Description: set time sync slave id.
   */
  virtual com::types::ErrorCode SetSlaveId(IN uint8_t slaveDevId) = 0;

  /*
   * Function: Enable
   * Arguments:
   * Return: ErrorCode
   * Description: enables the timesync slave.
   */
  virtual com::types::ErrorCode Enable() = 0;

  /*
   * Function: Disable
   * Arguments:
   * Return: ErrorCode
   * Description: disables the timesync slave.
   */
  virtual com::types::ErrorCode Disable() = 0;
  virtual uint16_t GetMajorVer() const = 0;
  virtual uint16_t GetMinorVer() const = 0;
  virtual uint16_t GetPatchVer() const = 0;
};

}  // namespace master
}  // namespace com

#endif  // EXTERNAL__TIMESYNCSLAVEIFACE_H_
