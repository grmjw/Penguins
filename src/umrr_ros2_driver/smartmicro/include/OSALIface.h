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

#ifndef OSALIFACE_H_
#define OSALIFACE_H_

#include <OSALTypes.h>

#include <functional>
#include <list>
#include <memory>
#include <set>
#include <string>

namespace osal
{
typedef std::function<void(osal::types::BufferDescriptor &)> ReceiverCallback;

class OSALIface
{
public:
  OSALIface() {}
  virtual ~OSALIface() {}

  /*  
     * Function: GetOSAL()
     * Arguments: none
     * Return: std::shared_ptr<OSALIface>
     * Description: Returns a singletone instance of a this class, since this is only
     *   an abstract class , the instantiation should be done by a deriving class.
     */
  static std::shared_ptr<OSALIface> GetOSAL();

  /*  
     * Function: Init
     * Arguments: IN const std::string& configPath 
     * Return: bool
     * Description: Initializes the osal layer
     */
  virtual bool Init(IN const std::string & configPath) = 0;

  /*  
     * Function: GetHwIfaces
     * Arguments: UT std::list<std::shared_ptr<HwIfaceDescriptor
     * Return: bool
     * Description: Retreive a list of available hw devices and those config
     */
  virtual bool GetHwIfaces(OUT std::list<std::shared_ptr<osal::types::HwIfaceDescriptor>> &) = 0;
  /*
     * Function: RegisterReceiver
     * Arguments: IN const HwRegistry& registry - hw desciption 
     *            IN ReceiverCallback callback - callback function which should be
     *                                      called upon a reception of a package
     * Return: ErrorCode
     * Description: Registers a receiver callback function for the given hw device , 
     *   which should be called, when a new buffer arrives.
     */

  virtual osal::types::ErrorCode RegisterReceiver(
    IN const osal::types::HwRegistry & registry, IN ReceiverCallback callback) = 0;
  /*
     * Function: UnRegisterReceiver
     * Arguments: IN IN const HwRegistry& registry - hw desciption 
     * Return: ErrorCode
     * Description: UnRegisters a receiver callback function for the given hw device , 
     */
  virtual osal::types::ErrorCode UnRegisterReceiver(
    IN const osal::types::HwRegistry & registry) = 0;
  /*  
     * Function: SendData
     * Arguments: IN const HwRegistry& registry - hw desciption
     *            IN BufferDescriptor& buffer - data buffer.
     * Return: ErrorCode
     * Description: Streams a data buffer over the given hw device
     */
  virtual osal::types::ErrorCode SendData(
    IN const osal::types::HwRegistry & registry,
    IN const osal::types::BufferDescriptor & buffer) = 0;
};

}  // namespace osal

#endif  // OSALIFACE_H_
