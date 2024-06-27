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

#ifndef EXTERNAL__TIMESYNCMASTERIFACE_H_
#define EXTERNAL__TIMESYNCMASTERIFACE_H_

#include <ExternalTypes.h>
#include <VersionedIface.h>

#include <functional>
#include <memory>

namespace com {
namespace master {
typedef std::function<bool(uint64_t &)> GetRefTimeCallback;

class EXPORT_SMART_ACCESS_LIB TimeSyncMasterIface : public com::VersionedIface {
 public:
  TimeSyncMasterIface() {}
  virtual ~TimeSyncMasterIface() {}
  /*
   * Function: Get()
   * Arguments: none
   * Return: std::shared_ptr<TimeSyncMasterIface>
   * Description: Returns a singletone instance of a this class, since this is
   * only an abstract class, the instantiation should be done by a deriving
   * class.
   */
  static std::shared_ptr<TimeSyncMasterIface> Get();

  /*
   * Function: RegisterRefTimeCallback
   * Arguments: GetRefTimeCallback
   * Return: ErrorCode
   * Description: Register a callback to get master reference time
   */
  virtual com::types::ErrorCode RegisterRefTimeCallback(
      IN GetRefTimeCallback callback) = 0;

  /*
   * Function: AddSlave
   * Arguments: uint8_t slaveDevId slave device id[0..15]
   * Return: ErrorCode
   * Description: adds a time sync slave to be synchronized
   */
  virtual com::types::ErrorCode AddSlave(IN uint8_t slaveDevId) = 0;

  /*
   * Function: RemoveSlave
   * Arguments: uint8_t slaveDevId slave device id[0..15]
   * Return: ErrorCode
   * Description: removes a time sync slave.
   */
  virtual com::types::ErrorCode RemoveSlave(IN uint8_t slaveDevId) = 0;

  /*
   * Function: Start
   * Arguments:
   * Return: ErrorCode
   * Description: start time sync master
   */
  virtual com::types::ErrorCode Start() = 0;
  /*
   * Function: Stop
   * Arguments:
   * Return: ErrorCode
   * Description: stops time sync master
   */
  virtual com::types::ErrorCode Stop() = 0;

  virtual uint16_t GetMajorVer() const = 0;
  virtual uint16_t GetMinorVer() const = 0;
  virtual uint16_t GetPatchVer() const = 0;
};

}  // namespace master
}  // namespace com

#endif  // EXTERNAL__TIMESYNCMASTERIFACE_H_
