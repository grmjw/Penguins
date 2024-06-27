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

#ifndef COM_MASTER_UMRR9D_T152_AUTOMOTIVE_V1_2_2_COMTARGETLIST_TARGETLISTHEADER_H
#define COM_MASTER_UMRR9D_T152_AUTOMOTIVE_V1_2_2_COMTARGETLIST_TARGETLISTHEADER_H

#include <ExternalTypes.h>
#include <VersionedIface.h>


#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr9d_t152_automotive_v1_2_2
{
namespace comtargetlist
{

// Forward Declarations



class TargetListHeader : public com::VersionedIface
{
public:
    TargetListHeader() {}

    virtual ~TargetListHeader() {}

    ///
    /// ACCESS FUNCTIONS
    ///

    /*!
     * Cycle Time
     */
    virtual com::types::float32_t GetCycleTime() const = 0;
    /*!
     * Number of valid targets in the current target list
     */
    virtual uint16_t GetNumberOfTargets() const = 0;
    /*!
     * Active TX-antenna index during data acquisition
     */
    virtual uint8_t GetAcquisitionTxAntIdx() const = 0;
    /*!
     * Active sweep index during data acquisition
     */
    virtual uint8_t GetAcquisitionSweepIdx() const = 0;
    /*!
     * Active center frequency index during data acquisition
     */
    virtual uint8_t GetAcquisitionCfIdx() const = 0;
    /*!
     * Used PRF Setting during acquisition, index/set: 0..2 first set; 3..5 second set
     */
    virtual uint8_t GetPrf() const = 0;
    /*!
     * Typical value of speed misinterpreations in this cycle
     */
    virtual com::types::float32_t GetUmambiguousSpeed() const = 0;
    /*!
     * Start of radar acquisition for target list (NTP coded)
     */
    virtual uint64_t GetAcquisitionStart() const = 0;

};
}  // comtargetlist
}  // umrr9d_t152_automotive_v1_2_2
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR9D_T152_AUTOMOTIVE_V1_2_2_COMTARGETLIST_TARGETLISTHEADER_H