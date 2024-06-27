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

#ifndef COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_1_1_COMTARGETBASELIST_TARGETLISTHEADER_H
#define COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_1_1_COMTARGETBASELIST_TARGETLISTHEADER_H

#include <ExternalTypes.h>
#include <VersionedIface.h>


#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr9f_t169_automotive_v2_1_1
{
namespace comtargetbaselist
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
     * Cycle Time of the radar. Cycle time could vary depending on the mode of operation of the radar.
     */
    virtual com::types::float32_t GetCycleDuration() const = 0;
    /*!
     * Number of the targets detected by the radar.
     */
    virtual uint8_t GetNumberOfTargets() const = 0;
    /*!
     *  Keeps a count of the total cycle durations that the radar has undergone since reboot starting from zero 
     *  
     */
    virtual uint32_t GetCycleCount() const = 0;
    /*!
     * Feedback channel of used Acquisition setup
     */
    virtual uint8_t GetAcquisitionSetup() const = 0;
    /*!
     * TimeStamp in seconds at which the data acquisition(radar ramps) starts.
     */
    virtual uint32_t GetTimeStamp() const = 0;
    /*!
     *  Timestamp(64Bit) is divided into two fields, first the timestamp(s) and second(AcqTimeStampFraction) which is the fraction part of the timestamp(s) 
     *  
     */
    virtual com::types::float32_t GetAcqTimeStampFraction() const = 0;

};
}  // comtargetbaselist
}  // umrr9f_t169_automotive_v2_1_1
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_1_1_COMTARGETBASELIST_TARGETLISTHEADER_H