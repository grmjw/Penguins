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

#ifndef COM_MASTER_UMRR11_T132_MSE_V1_1_1_COMDYNAMICSPORT_STATICPORTHEADER_H
#define COM_MASTER_UMRR11_T132_MSE_V1_1_1_COMDYNAMICSPORT_STATICPORTHEADER_H

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
namespace comdynamicsport
{

// Forward Declarations



class StaticPortHeader : public com::VersionedIface
{
public:
    StaticPortHeader() {}

    virtual ~StaticPortHeader() {}

    ///
    /// ACCESS FUNCTIONS
    ///

    /*!
     *  Dynamics Source 
     */
    virtual uint8_t GetDynamicsSource() const = 0;
    /*!
     *  Ego Speed 
     */
    virtual com::types::float32_t GetSpeed() const = 0;
    /*!
     *  Ego Speed Quality 
     */
    virtual com::types::float32_t GetSpeedQuality() const = 0;
    /*!
     *  Ego Yaw Rate  
     */
    virtual com::types::float32_t GetYawRate() const = 0;
    /*!
     *  Ego Yaw Rate Quality  
     */
    virtual com::types::float32_t GetYawRateQuality() const = 0;

};
}  // comdynamicsport
}  // umrr11_t132_mse_v1_1_1
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR11_T132_MSE_V1_1_1_COMDYNAMICSPORT_STATICPORTHEADER_H