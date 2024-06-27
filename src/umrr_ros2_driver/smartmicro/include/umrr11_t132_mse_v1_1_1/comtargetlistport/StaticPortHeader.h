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

#ifndef COM_MASTER_UMRR11_T132_MSE_V1_1_1_COMTARGETLISTPORT_STATICPORTHEADER_H
#define COM_MASTER_UMRR11_T132_MSE_V1_1_1_COMTARGETLISTPORT_STATICPORTHEADER_H

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
namespace comtargetlistport
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
     *  Cycle Time 
     */
    virtual com::types::float32_t GetCycleTime() const = 0;
    /*!
     *  Provides the number of target in the port  
     */
    virtual uint16_t GetNumberOfTargets() const = 0;

};
}  // comtargetlistport
}  // umrr11_t132_mse_v1_1_1
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR11_T132_MSE_V1_1_1_COMTARGETLISTPORT_STATICPORTHEADER_H