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

#ifndef COM_MASTER_UMRR96_T153_AUTOMOTIVE_V1_2_2_COMTARGETLIST_PORTHEADER_H
#define COM_MASTER_UMRR96_T153_AUTOMOTIVE_V1_2_2_COMTARGETLIST_PORTHEADER_H

#include <ExternalTypes.h>
#include <VersionedIface.h>


#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr96_t153_automotive_v1_2_2
{
namespace comtargetlist
{

// Forward Declarations



class PortHeader : public com::VersionedIface
{
public:
    PortHeader() {}

    virtual ~PortHeader() {}

    ///
    /// ACCESS FUNCTIONS
    ///

    /*!
     * Unique port identifier
     */
    virtual uint32_t GetPortIdentifier() const = 0;
    /*!
     * Major port version
     */
    virtual int16_t GetPortVersionMajor() const = 0;
    /*!
     * Minor port version
     */
    virtual int16_t GetPortVersionMinor() const = 0;
    /*!
     * A timestamp
     */
    virtual uint64_t GetTimestamp() const = 0;
    /*!
     * Port size (includes this header)
     */
    virtual uint32_t GetPortSize() const = 0;
    /*!
     * Port body endianness[1:big endian][2:little endian]
     */
    virtual uint8_t GetBodyEndianness() const = 0;
    /*!
     * To identify multiple instances of the same port
     */
    virtual uint8_t GetPortIndex() const = 0;
    /*!
     * Generic port header major version
     */
    virtual uint8_t GetHeaderVersionMajor() const = 0;
    /*!
     * Generic port header minor version
     */
    virtual uint8_t GetHeaderVersionMinor() const = 0;

};
}  // comtargetlist
}  // umrr96_t153_automotive_v1_2_2
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR96_T153_AUTOMOTIVE_V1_2_2_COMTARGETLIST_PORTHEADER_H