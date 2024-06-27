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

#ifndef EXTERNAL__TIMESYNCSERVICEIFACE_H_
#define EXTERNAL__TIMESYNCSERVICEIFACE_H_

#include <ExternalTypes.h>
#include <Instruction.h>
#include <InstructionBatch.h>
#include <VersionedIface.h>

#include <functional>
#include <memory>
#include <set>

namespace com {
namespace master {
class TimeSyncMasterIface;
class TimeSyncSlaveIface;

class EXPORT_SMART_ACCESS_LIB TimeSyncServiceIface
    : public com::VersionedIface {
 public:
  TimeSyncServiceIface() {}
  virtual ~TimeSyncServiceIface() {}

  /*
   * Function: Get()
   * Arguments: none
   * Return: std::shared_ptr<TimeSyncServiceIface>
   * Description: Returns a singletone instance of a this class, since this is
   * only an abstract class, the instantiation should be done by a deriving
   * class.
   */
  static std::shared_ptr<TimeSyncServiceIface> Get();

  /*
   * Function: Init
   * Arguments: none
   * Return: bool
   * Description: Initializes the time sync services.
   */
  virtual bool Init() = 0;

  /*
   * Function: GetSlaveService()
   * Arguments: none
   * Return: std::shared_ptr<TimeSyncServiceSlaveIface>
   * Description: Returns a singletone instance of time sync slave service,
   *  return nullptr if the tyme sync role set to master or the feature is
   * disabled
   */
  virtual std::shared_ptr<TimeSyncSlaveIface> GetSlaveService() = 0;

  /*
   * Function: GetMasterIface()
   * Arguments: none
   * Return: std::shared_ptr<TimeSyncServiceMasterIface>
   * Description: Returns a singletone instance of time sync master service,
   *  return nullptr if the tyme sync role set to slave or the feature is
   * disabled
   */
  virtual std::shared_ptr<TimeSyncMasterIface> GetMasterService() = 0;

  virtual uint16_t GetMajorVer() const = 0;
  virtual uint16_t GetMinorVer() const = 0;
  virtual uint16_t GetPatchVer() const = 0;
};

}  // namespace master
}  // namespace com

#endif  // EXTERNAL__TIMESYNCSERVICEIFACE_H_
