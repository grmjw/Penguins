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

#ifndef EXTERNAL__UPDATESERVICEIFACE_H_
#define EXTERNAL__UPDATESERVICEIFACE_H_

#include <ExternalTypes.h>
#include <VersionedIface.h>

#include <functional>
#include <memory>
#include <set>
#include <string>

namespace com {
namespace master {
typedef std::function<void(com::types::SWUpdateInfo &)> SWUpdateCallback;

class EXPORT_SMART_ACCESS_LIB UpdateServiceIface : public com::VersionedIface {
 public:
  UpdateServiceIface() {}
  virtual ~UpdateServiceIface() {}

  /*
   * Function: Get()
   * Arguments: none
   * Return: std::shared_ptr<UpdateServiceIface>
   * Description:
   * Returns a singletone instance of a this class, since this is only
   * an abstract class, the instantiation should be done by a deriving class.
   */
  static std::shared_ptr<UpdateServiceIface> Get();

  /*
   * Function: Init
   * Arguments: none
   * Return: bool
   * Description: Initializes the update service layer.
   */
  virtual bool Init() = 0;

  /*
   * Function:    SoftwareUpdate
   *
   * Arguments:   IN std::string& updateImage  | Path to Update-Imagefile
   *              IN ClientId clientID         | Target-Sensor ClientID
   *              IN SWUpdateCallback callback | Callback-Function for
   * Update-Info
   *
   * Return:      ErrorCode
   *
   * Description: Function for starting a new Update-Service
   */
  virtual com::types::ErrorCode SoftwareUpdate(
      IN std::string &updateImage, IN com::types::ClientId clientID,
      IN SWUpdateCallback callback) = 0;
  /*
   * Function:    AbortSoftwareUpdate
   *
   * Arguments:   None
   *
   * Return:      void
   *
   * Description:  Function for aborting the current running Update-Service
   */
  virtual void AbortSoftwareUpdate() = 0;
};

}  // namespace master
}  // namespace com

#endif  // EXTERNAL__UPDATESERVICEIFACE_H_
