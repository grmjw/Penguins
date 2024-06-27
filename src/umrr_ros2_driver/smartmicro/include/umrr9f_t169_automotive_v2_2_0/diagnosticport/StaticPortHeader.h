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

#ifndef COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_2_0_DIAGNOSTICPORT_STATICPORTHEADER_H
#define COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_2_0_DIAGNOSTICPORT_STATICPORTHEADER_H

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
namespace diagnosticport
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
     * Number of diagnostics that are in the dynamic part of the port.
     */
    virtual uint16_t GetnumberOfDiagnostics() const = 0;
    /*!
     *  The Summarized Status field is set to the most critical diagnostic status that is listed in the dynamic part of the port 
     *  
     */
    virtual uint8_t GetsummarizedStatus() const = 0;
    /*!
     * 0 = No timestamp is set, 1 = Raw timestamp in microseconds, 2 = NTP format
     */
    virtual uint8_t GettimestampFormat() const = 0;
    /*!
     * Timestamp when the data was collected
     */
    virtual uint64_t Gettimestamp() const = 0;

};
}  // diagnosticport
}  // umrr9f_t169_automotive_v2_2_0
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR9F_T169_AUTOMOTIVE_V2_2_0_DIAGNOSTICPORT_STATICPORTHEADER_H