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

#ifndef COM_MASTER_UMRR11_T132_MSE_V1_1_1_COMOBJECTLISTPORT_OBJECT_H
#define COM_MASTER_UMRR11_T132_MSE_V1_1_1_COMOBJECTLISTPORT_OBJECT_H

#include <ExternalTypes.h>
#include <VersionedIface.h>


#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr11_t132_mse_v1_1_1
{
namespace comobjectlistport
{

// Forward Declarations



class Object : public com::VersionedIface
{
public:
    Object() {}

    virtual ~Object() {}

    ///
    /// ACCESS FUNCTIONS
    ///

    /*!
     *  X component of the position 
     */
    virtual com::types::float32_t GetxPos() const = 0;
    /*!
     *  Y component of the position 
     */
    virtual com::types::float32_t GetyPos() const = 0;
    /*!
     *  Z component of the position 
     */
    virtual com::types::float32_t GetzPos() const = 0;
    /*!
     *  Absolute object speed 
     */
    virtual com::types::float32_t GetSpeedAbsolute() const = 0;
    /*!
     *  Heading of an object 
     */
    virtual com::types::float32_t GetHeading() const = 0;
    /*!
     *  Length of an object 
     */
    virtual com::types::float32_t GetLength() const = 0;
    /*!
     *  Quality of an object 
     */
    virtual com::types::float32_t GetQuality() const = 0;
    /*!
     *  Acceleration of an object 
     */
    virtual com::types::float32_t GetAcceleration() const = 0;
    /*!
     *  unique tag number for identification of the object  
     */
    virtual uint16_t GetObjectID() const = 0;
    /*!
     *  0 = Object, 2 = Guardrail  
     */
    virtual uint8_t GetStatus() const = 0;

};
}  // comobjectlistport
}  // umrr11_t132_mse_v1_1_1
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR11_T132_MSE_V1_1_1_COMOBJECTLISTPORT_OBJECT_H