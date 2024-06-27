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

#ifndef COM_MASTER_UMRR11_T132_AUTOMOTIVE_V1_1_1_COMTARGETLISTPORT_GENERICPORTHEADER_H
#define COM_MASTER_UMRR11_T132_AUTOMOTIVE_V1_1_1_COMTARGETLISTPORT_GENERICPORTHEADER_H

#include <ExternalTypes.h>
#include <VersionedIface.h>


#include <memory>
#include <vector>

namespace com
{
namespace master
{
namespace umrr11_t132_automotive_v1_1_1
{
namespace comtargetlistport
{

// Forward Declarations



class GenericPortHeader : public com::VersionedIface
{
public:
    GenericPortHeader() {}

    virtual ~GenericPortHeader() {}

    ///
    /// ACCESS FUNCTIONS
    ///

    /*!
     * Port identification number.
     */
    virtual uint32_t GetPortId() const = 0;
    /*!
     * Major version of the port API.
     */
    virtual int16_t GetPortVersionMajor() const = 0;
    /*!
     * Minor version of the port API.
     */
    virtual int16_t GetPortVersionMinor() const = 0;
    /*!
     * Time of creation of the port.
     */
    virtual uint64_t GetTimestamp() const = 0;
    /*!
     * Size of the port including this header.
     */
    virtual uint32_t GetPortSize() const = 0;
    /*!
     *  Endianness of the sensor system 
     * Please notice that the data will be presented in the host endianness, and should not be reversed 
     *  
     */
    virtual uint8_t GetBodyEndianness() const = 0;
    /*!
     * The port index is used for multiple occurance of ports with the same port identifier. 
     */
    virtual uint8_t GetPortIndex() const = 0;
    /*!
     * Major version of the generic port API.
     */
    virtual uint8_t GetHeaderVersionMajor() const = 0;
    /*!
     * Minor version of the generic port API. 
     */
    virtual uint8_t GetHeaderVersionMinor() const = 0;

};
}  // comtargetlistport
}  // umrr11_t132_automotive_v1_1_1
}  // namespace master
}  // namespace com

#endif  // COM_MASTER_UMRR11_T132_AUTOMOTIVE_V1_1_1_COMTARGETLISTPORT_GENERICPORTHEADER_H