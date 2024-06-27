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

#ifndef COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_1_1_COMTARGETBASELIST_TARGET_H
#define COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_1_1_COMTARGETBASELIST_TARGET_H

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
     * Azimuth angle of the target
     */
    virtual com::types::float32_t GetAzimuthAngle() const = 0;
    /*!
     * Elevation angle of the target
     */
    virtual com::types::float32_t GetElevationAngle() const = 0;
    /*!
     * The radar cross section of the target in decibels.
     */
    virtual com::types::float32_t GetRCS() const = 0;
    /*!
     * Power of the detected target in decibels.
     */
    virtual com::types::float32_t GetSignalLevel() const = 0;
    /*!
     * Noise of the detected target in decibels.
     */
    virtual com::types::float32_t GetNoise() const = 0;

};
}  // comtargetbaselist
}  // umrr9f_t169_automotive_v2_1_1
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_1_1_COMTARGETBASELIST_TARGET_H