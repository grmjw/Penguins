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

#ifndef COM_MASTER_UMRR11_T132_AUTOMOTIVE_V1_1_2_COMTARGETLIST_TARGETLISTHEADER_H
#define COM_MASTER_UMRR11_T132_AUTOMOTIVE_V1_1_2_COMTARGETLIST_TARGETLISTHEADER_H

#include <ExternalTypes.h>
#include <VersionedIface.h>


#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr11_t132_automotive_v1_1_2
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
     * Cycle Time of the radar. Cycle time could vary depending on the mode of operation of the radar.
     */
    virtual com::types::float32_t GetCycleTime() const = 0;
    /*!
     * Number of the detected targets.
     */
    virtual uint16_t GetNumberOfTargets() const = 0;
    /*!
     * Feedback channel of used Acquisition setup
     */
    virtual uint16_t GetAcquisitionSetup() const = 0;

};
}  // comtargetlist
}  // umrr11_t132_automotive_v1_1_2
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR11_T132_AUTOMOTIVE_V1_1_2_COMTARGETLIST_TARGETLISTHEADER_H