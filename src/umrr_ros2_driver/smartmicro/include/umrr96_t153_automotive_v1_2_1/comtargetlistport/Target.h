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

#ifndef COM_MASTER_UMRR96_T153_AUTOMOTIVE_V1_2_1_COMTARGETLISTPORT_TARGET_H
#define COM_MASTER_UMRR96_T153_AUTOMOTIVE_V1_2_1_COMTARGETLISTPORT_TARGET_H

#include <ExternalTypes.h>
#include <VersionedIface.h>


#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr96_t153_automotive_v1_2_1
{
namespace comtargetlistport
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
     *  Target range  
     */
    virtual com::types::float32_t GetRange() const = 0;
    /*!
     *  Target speed 
     */
    virtual com::types::float32_t GetSpeedRadial() const = 0;
    /*!
     *  Azimuth angle of the target  
     */
    virtual com::types::float32_t GetAzimuthAngle() const = 0;
    /*!
     *  Elevation angle of the target  
     */
    virtual com::types::float32_t GetElevationAngle() const = 0;
    /*!
     *  The Radar Cross Section of the target 
     */
    virtual com::types::float32_t GetRCS() const = 0;
    /*!
     *  Amplitude of the target  
     */
    virtual com::types::float32_t GetPower() const = 0;
    /*!
     *  Noise of the target  
     */
    virtual com::types::float32_t GetTgtNoise() const = 0;

};
}  // comtargetlistport
}  // umrr96_t153_automotive_v1_2_1
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR96_T153_AUTOMOTIVE_V1_2_1_COMTARGETLISTPORT_TARGET_H