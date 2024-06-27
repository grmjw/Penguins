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

#ifndef EXTERNAL__COMMUNICATIONSERVICESIFACE_H_
#define EXTERNAL__COMMUNICATIONSERVICESIFACE_H_

#include <DeviceMonitorServiceIface.h>
#include <ExternalTypes.h>
#include <Instruction.h>
#include <InstructionBatch.h>
#include <InstructionServiceIface.h>
#include <TimeSyncMasterIface.h>
#include <TimeSyncServiceIface.h>
#include <TimeSyncSlaveIface.h>
#include <UpdateServiceIface.h>
#include <VersionedIface.h>

#include <memory>

namespace com {
namespace master {
// Forward-Declarations
class InstructionServiceIface;
class TimeSyncServiceIface;
class UpdateServiceIface;
class DeviceMonitorServiceIface;

class EXPORT_SMART_ACCESS_LIB CommunicationServicesIface
    : public com::VersionedIface {
 public:
  CommunicationServicesIface() {}
  virtual ~CommunicationServicesIface() {}

  /*
   * Function: Get()
   * Arguments: none
   * Return: std::shared_ptr<InstructionServiceIface>
   * Description: Returns a singletone instance of a this class, since this is
   * only an abstract class, the instantiation should be done by a deriving
   * class.
   */
  static std::shared_ptr<CommunicationServicesIface> Get();

  /*
   * Function: Init
   * Arguments: none
   * Return: bool
   * Description: Initializes the commuinication services layer.
   */
  virtual bool Init() = 0;

  /*
   * Function: GetInstructionService
   * Arguments: none
   * Return:    std::shared_ptr<InstructionServiceIface>
   * Description: Return shared pointer to instruction service
   */
  virtual std::shared_ptr<InstructionServiceIface> GetInstructionService()
      const = 0;

  /*
   * Function: GetTimeSyncServiceIface()
   * Arguments: none
   * Return: bool
   * Description: Return shared pointer to time sync service
   */
  virtual std::shared_ptr<TimeSyncServiceIface> GetTimeSyncServiceIface()
      const = 0;

  /*
   * Function: GetUpdateService()
   * Arguments: none
   * Return:    std::shared_ptr<UpdateServiceIface>
   * Description: Return shared pointer to update service
   */
  virtual std::shared_ptr<UpdateServiceIface> GetUpdateService() const = 0;

  /*
   * Function:    GetDeviceMonitorService()
   * Arguments:   none
   * Return:      bool
   * Description: Returns shared pointer to DeviceMonitor service
   */
  virtual std::shared_ptr<DeviceMonitorServiceIface> GetDeviceMonitorService()
      const = 0;
};

}  // namespace master
}  // namespace com

#endif  // EXTERNAL__COMMUNICATIONSERVICESIFACE_H_
