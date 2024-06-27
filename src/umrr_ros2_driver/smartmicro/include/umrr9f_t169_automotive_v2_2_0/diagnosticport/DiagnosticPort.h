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

#ifndef COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_2_0_DIAGNOSTICPORT_DIAGNOSTICPORT_H
#define COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_2_0_DIAGNOSTICPORT_DIAGNOSTICPORT_H

#include <ExternalTypes.h>
#include <VersionedIface.h>

#include <umrr9f_t169_automotive_v2_2_0/diagnosticport/GenericPortHeader.h>
#include <umrr9f_t169_automotive_v2_2_0/diagnosticport/StaticPortHeader.h>
#include <umrr9f_t169_automotive_v2_2_0/diagnosticport/DiagnosticObject.h>

#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr9f_t169_automotive_v2_2_0
{
namespace diagnosticport
{

// Forward Declarations

class GenericPortHeader;
class StaticPortHeader;
class DiagnosticObject;


class DiagnosticPort : public com::VersionedIface
{
public:
    DiagnosticPort() {}

    virtual ~DiagnosticPort() {}

    ///
    /// ACCESS FUNCTIONS
    ///

    /*!
     * No description available
     */
    virtual std::shared_ptr<GenericPortHeader> GetGenericPortHeader() const = 0;
    /*!
     * No description available
     */
    virtual std::shared_ptr<StaticPortHeader> GetStaticPortHeader() const = 0;
    /*!
     *  Collection of Diagnostic Outputs
     */
    virtual const std::vector<std::shared_ptr<DiagnosticObject>>& GetDiagnosticObjectList() const = 0;

};
}  // diagnosticport
}  // umrr9f_t169_automotive_v2_2_0
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_2_0_DIAGNOSTICPORT_DIAGNOSTICPORT_H