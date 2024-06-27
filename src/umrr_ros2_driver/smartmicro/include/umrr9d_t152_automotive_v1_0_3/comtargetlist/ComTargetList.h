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

#ifndef COM_MASTER_UMRR9D_T152_AUTOMOTIVE_V1_0_3_COMTARGETLIST_COMTARGETLIST_H
#define COM_MASTER_UMRR9D_T152_AUTOMOTIVE_V1_0_3_COMTARGETLIST_COMTARGETLIST_H

#include <ExternalTypes.h>
#include <VersionedIface.h>

#include <umrr9d_t152_automotive_v1_0_3/comtargetlist/PortHeader.h>
#include <umrr9d_t152_automotive_v1_0_3/comtargetlist/TargetListHeader.h>
#include <umrr9d_t152_automotive_v1_0_3/comtargetlist/Target.h>

#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr9d_t152_automotive_v1_0_3
{
namespace comtargetlist
{

// Forward Declarations

class PortHeader;
class TargetListHeader;
class Target;


class ComTargetList : public com::VersionedIface
{
public:
    ComTargetList() {}

    virtual ~ComTargetList() {}

    ///
    /// ACCESS FUNCTIONS
    ///

    /*!
     * smartmicro Generic Port Header
     */
    virtual std::shared_ptr<PortHeader> GetPortHeader() const = 0;
    /*!
     * Static header of the target list
     */
    virtual std::shared_ptr<TargetListHeader> GetTargetListHeader() const = 0;
    /*!
     * Represent a single target
     */
    virtual const std::vector<std::shared_ptr<Target>>& GetTargetList() const = 0;

};
}  // comtargetlist
}  // umrr9d_t152_automotive_v1_0_3
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR9D_T152_AUTOMOTIVE_V1_0_3_COMTARGETLIST_COMTARGETLIST_H