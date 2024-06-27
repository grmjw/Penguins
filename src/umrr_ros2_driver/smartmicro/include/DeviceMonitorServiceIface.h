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

#ifndef EXTERNAL__DEVICEMONITORSERVICEIFACE_H_
#define EXTERNAL__DEVICEMONITORSERVICEIFACE_H_

#include <ExternalTypes.h>
#include <VersionedIface.h>

#include <functional>
#include <memory>
#include <set>
#include <vector>

namespace com {
namespace master {
typedef std::function<void(com::types::ClientId id, bool clientConnectedStatus)>
    ConnectedClientCallback;

class EXPORT_SMART_ACCESS_LIB DeviceMonitorServiceIface
    : public com::VersionedIface {
 public:
  DeviceMonitorServiceIface() {}
  virtual ~DeviceMonitorServiceIface() {}

  /*
   * Function:    Get()
   * Arguments:   none
   * Return:      std::shared_ptr<DeviceMonitorServiceIface>
   * Description: Returns a singletone instance of a this class, since this is
   * only an abstract class, the instantiation should be done by a deriving
   * class.
   */
  static std::shared_ptr<DeviceMonitorServiceIface> Get();

  /*
   * Function:    Init
   * Arguments:   none
   * Return:      bool
   * Description: Initializes the deviceMonitor service layer
   */
  virtual bool Init() = 0;

  /*
   * Function:    RegisterConnectedClientCallback
   * Arguments:   IN ConnectedClientCallback callback
   *              Callback-Function which shall be called to inform about
   *              change in 'connected client list'
   * Return:      ErrorCode
   * Description: Registers the ConnectedClientCallback
   */
  virtual com::types::ErrorCode RegisterConnectedClientCallback(
      IN ConnectedClientCallback callback) = 0;

  /*
   * Function:    GetConnectedClientInfo
   * Arguments:   OUT std::vector<ConnectedClientInfo>& clientInfo
   * Return:      bool
   * Description: Returns true if the list with clientInfos of connected clients
   *              is available in reference clientInfo
   */
  virtual bool GetConnectedClientInfo(
      OUT std::vector<com::types::ConnectedClientInfo>& clientInfo) = 0;

  /*
   * Function:    IsClientConnected
   * Arguments:   IN ClientId clientId - destination client id
   * Return:      bool
   * Description: Returns true if the client with given client id is connected
   */
  virtual bool IsClientConnected(IN com::types::ClientId clientId) = 0;

  /*
   * Function:    GetUserInterface
   * Arguments:
   * Return:      bool
   * Description: Returns name + version of UserInterface
   */
  // ToDo...........
};

}  // namespace master
}  // namespace com

#endif  // EXTERNAL__DEVICEMONITORSERVICEIFACE_H_
