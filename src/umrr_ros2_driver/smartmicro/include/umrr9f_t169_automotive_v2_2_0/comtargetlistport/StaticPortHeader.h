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

#ifndef COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_2_0_COMTARGETLISTPORT_STATICPORTHEADER_H
#define COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_2_0_COMTARGETLISTPORT_STATICPORTHEADER_H

#include <ExternalTypes.h>
#include <VersionedIface.h>


#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr9f_t169_automotive_v2_2_0
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
    /*!
     *  TX Antenna index used for aquisition 
     */
    virtual uint8_t GetAcquisitionTx() const = 0;
    /*!
     *  Sweep index used for aquisition 
     */
    virtual uint8_t GetAcquisitionSweep() const = 0;
    /*!
     *  Center Frequency index used for aquisition 
     */
    virtual uint8_t GetAcquisitionCf() const = 0;
    /*!
     *  Index of PRF setting used for aquisition 
     */
    virtual uint8_t GetAcquisitionPrfIdx() const = 0;
    /*!
     *  Unambiguous Speed in this cycle 
     */
    virtual com::types::float32_t GetUmambiguousSpeed() const = 0;
    /*!
     *  Start of Radar Acquisition for target list (NTP coded) 
     */
    virtual uint64_t GetAcquisitionStart() const = 0;

};
}  // comtargetlistport
}  // umrr9f_t169_automotive_v2_2_0
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_2_0_COMTARGETLISTPORT_STATICPORTHEADER_H