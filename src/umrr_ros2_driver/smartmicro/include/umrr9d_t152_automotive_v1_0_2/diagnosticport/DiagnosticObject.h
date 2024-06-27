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

#ifndef COM_MASTER_UMRR9D_T152_AUTOMOTIVE_V1_0_2_DIAGNOSTICPORT_DIAGNOSTICOBJECT_H
#define COM_MASTER_UMRR9D_T152_AUTOMOTIVE_V1_0_2_DIAGNOSTICPORT_DIAGNOSTICOBJECT_H

#include <ExternalTypes.h>
#include <VersionedIface.h>


#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr9d_t152_automotive_v1_0_2
{
namespace diagnosticport
{

// Forward Declarations



class DiagnosticObject : public com::VersionedIface
{
public:
    DiagnosticObject() {}

    virtual ~DiagnosticObject() {}

    ///
    /// ACCESS FUNCTIONS
    ///

    /*!
     * Unique id for each diagnostic function
     */
    virtual uint16_t Getid() const = 0;
    /*!
     * Status of the diagnostic function
     */
    virtual uint8_t Getstatus() const = 0;
    /*!
     * Data type of the value field
     */
    virtual uint8_t GetdataType() const = 0;
    /*!
     * Value set by a diagnostic function
     */
    virtual uint64_t Getvalue() const = 0;

};
}  // diagnosticport
}  // umrr9d_t152_automotive_v1_0_2
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR9D_T152_AUTOMOTIVE_V1_0_2_DIAGNOSTICPORT_DIAGNOSTICOBJECT_H