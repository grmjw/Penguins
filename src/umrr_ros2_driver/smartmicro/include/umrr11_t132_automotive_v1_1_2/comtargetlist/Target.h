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

#ifndef COM_MASTER_UMRR11_T132_AUTOMOTIVE_V1_1_2_COMTARGETLIST_TARGET_H
#define COM_MASTER_UMRR11_T132_AUTOMOTIVE_V1_1_2_COMTARGETLIST_TARGET_H

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



class Target : public com::VersionedIface
{
public:
    Target() {}

    virtual ~Target() {}

    ///
    /// ACCESS FUNCTIONS
    ///

    /*!
     * Range of the detected target.
     */
    virtual com::types::float32_t GetRange() const = 0;
    /*!
     * Radial speed of the detected target.
     */
    virtual com::types::float32_t GetSpeedRadial() const = 0;
    /*!
     * Azimuth angle of the detected target.
     */
    virtual com::types::float32_t GetAzimuthAngle() const = 0;
    /*!
     * Elevation angle of the detected target.
     */
    virtual com::types::float32_t GetElevationAngle() const = 0;
    /*!
     * Variance of the range.
     */
    virtual com::types::float32_t GetVarianceRange() const = 0;
    /*!
     * Variance of the speed.
     */
    virtual com::types::float32_t GetVarianceSpeed() const = 0;
    /*!
     * Variance of the azimuth angle.
     */
    virtual com::types::float32_t GetVarianceAzimuthAngle() const = 0;
    /*!
     * Variance of the elevation angle.
     */
    virtual com::types::float32_t GetVarianceElevationAngle() const = 0;
    /*!
     * The radar cross section of the detected target.
     */
    virtual com::types::float32_t GetRCS() const = 0;
    /*!
     * Probability of the false alarm.
     */
    virtual com::types::float32_t GetFalseAlarmProbability() const = 0;
    /*!
     * Flags as bitwise OR operation of port_target_list_target_flags 'target flags'.
     */
    virtual uint32_t GetFlags() const = 0;
    /*!
     * Power of the detected target in decibels.
     */
    virtual com::types::float32_t GetPower() const = 0;
    /*!
     * Noise of the detected target in decibels.
     */
    virtual com::types::float32_t GetNoise() const = 0;
    /*!
     * Index of the peak in the peak list port (PLP) port that this target has been generated from.
     */
    virtual uint16_t GetPeakIdx() const = 0;

};
}  // comtargetlist
}  // umrr11_t132_automotive_v1_1_2
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR11_T132_AUTOMOTIVE_V1_1_2_COMTARGETLIST_TARGET_H