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

#ifndef COM_MASTER_UMRR11_T132_MSE_V1_1_1_DATA_SERVICE_IFACE_H
#define COM_MASTER_UMRR11_T132_MSE_V1_1_1_DATA_SERVICE_IFACE_H


#include <VersionedIface.h>
#include <ExternalTypes.h>
#include <umrr11_t132_mse_v1_1_1/comtargetlistport/ComTargetListPort.h>
#include <umrr11_t132_mse_v1_1_1/comobjectlistport/ComObjectListPort.h>
#include <umrr11_t132_mse_v1_1_1/comdynamicsport/ComDynamicsPort.h>
#include<functional>


namespace com
{
namespace master
{
namespace umrr11_t132_mse_v1_1_1
{

// FORWARD DECLARATIONS

namespace comtargetlistport {

class ComTargetListPort;

}
namespace comobjectlistport {

class ComObjectListPort;

}
namespace comdynamicsport {

class ComDynamicsPort;

}

// CALLBACKS
typedef std::function<void(std::shared_ptr<com::master::umrr11_t132_mse_v1_1_1::comtargetlistport::ComTargetListPort>, com::types::ClientId clientId)>
 ReceiveComTargetListPortCallback;
typedef std::function<void(std::shared_ptr<com::master::umrr11_t132_mse_v1_1_1::comobjectlistport::ComObjectListPort>, com::types::ClientId clientId)>
 ReceiveComObjectListPortCallback;
typedef std::function<void(std::shared_ptr<com::master::umrr11_t132_mse_v1_1_1::comdynamicsport::ComDynamicsPort>, com::types::ClientId clientId)>
 ReceiveComDynamicsPortCallback;

class EXPORT_USER_INTERFACE_LIB DataStreamServiceIface : public com::VersionedIface
{
public:
  DataStreamServiceIface() {}
  virtual ~DataStreamServiceIface() {}

  /*  
        * Function: Get()
        * Arguments: none
        * Return: std::shared_ptr<DataStreamServiceIface>
        * Description: Returns a singletone instance of a this class, since this is only
        * an abstract class, the instantiation should be done by a deriving class.
        */
  static std::shared_ptr<DataStreamServiceIface> Get();

  /*  
        * Function: Init
        * Arguments: none
        * Return: bool
        * Description: Initializes the commuincation data stream services layer.
        */
  virtual bool Init() = 0;

  // REGISTER CALLBACKS
    virtual com::types::ErrorCode RegisterComTargetListPortReceiveCallback(IN com::types::ClientId clientId, 
     IN ReceiveComTargetListPortCallback callback) = 0;
    virtual com::types::ErrorCode RegisterComObjectListPortReceiveCallback(IN com::types::ClientId clientId, 
     IN ReceiveComObjectListPortCallback callback) = 0;
    virtual com::types::ErrorCode RegisterComDynamicsPortReceiveCallback(IN com::types::ClientId clientId, 
     IN ReceiveComDynamicsPortCallback callback) = 0;

};
} // namespace umrr11_t132_mse_v1_1_1
} // namespace master
} // namespace com 

#endif // COM_MASTER_UMRR11_T132_MSE_V1_1_1_DATA_SERVICE_IFACE_H