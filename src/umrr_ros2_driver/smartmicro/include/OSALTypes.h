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

#ifndef OSAL_TYPES_H
#define OSAL_TYPES_H
#include <stdint.h>
#include <memory>
#include <set>
#include <string>

#define IN
#define OUT
#define INOUT
#define CAN_MAX_DATA_BYTES 8

namespace osal {
namespace types {

typedef float           float32_t;
typedef uint32_t        ClientId;
typedef uint16_t        PortId;
typedef uint8_t         CanDevId;
typedef uint8_t         SerialDevId;
typedef uint16_t        CanId;

typedef struct
{
   uint16_t u16_identifier;
   uint8_t  u8_dlc;
   uint8_t  au8_data[CAN_MAX_DATA_BYTES];
} CanFormat;

enum ErrorCode {
    ERROR_CODE_OK = 0,
    ERROR_CODE_SERIALIZATION_ERROR,
    ERROR_CODE_REGISTRATION_ERROR,
    ERROR_CODE_CLIENT_DISCONNECTED,
    ERROR_CODE_UNKNOWN_CLIENT,
    ERROR_CODE_UNKNOWN_LINK,
    ERROR_CODE_GENERIC_ERROR
};

enum HwIfaceType {
    HW_IFACE_CAN = 0,
    HW_IFACE_ETH,
    HW_IFACE_RS485,
    HW_IFACE_UNKNOWN
};

enum EthTransportType {
    ETH_TRANSPORT_TYPE_TCP,
    ETH_TRANSPORT_TYPE_UDP,
    ETH_TRANSPORT_TYPE_MULTICAST
};

class BufferDescriptor 
{
public:
    BufferDescriptor(uint8_t* bufferPtr, size_t size)
    : _bufferPtr(bufferPtr),
    _size(size) 
    {
    }

    BufferDescriptor()
    : _bufferPtr(nullptr),
    _size(0) 
    {
    }

    ~BufferDescriptor()
    {
    }

    inline uint8_t* GetBufferPtr() const
    {
        return _bufferPtr; 
    }

    inline size_t GetSize() const
    {
        return _size;
    }

    inline void SetBufferPtr(IN uint8_t* bufferPtr)
    {
        _bufferPtr = bufferPtr;
    }

    inline void SetSize(IN size_t size)
    {
        _size = size;
    }

private:
    uint8_t*             _bufferPtr;
    size_t               _size;
};

class HwIfaceDescriptor{
public:
    HwIfaceDescriptor(){}
    HwIfaceDescriptor(HwIfaceType hwIfType)
    : _hwIfType(hwIfType){}
    virtual ~HwIfaceDescriptor(){}

    inline void SetHwIfaceType(IN HwIfaceType hwIfType)
    {
        _hwIfType = hwIfType;
    }
    
    inline HwIfaceType GetHwIfaceType() const 
    {
        return _hwIfType;
    }

private:
    HwIfaceType     _hwIfType;
};

class HwCanDescriptor : public HwIfaceDescriptor {
public:
    HwCanDescriptor(){}
    HwCanDescriptor(CanDevId deviceId,
                    const std::string& ifaceName,
                    uint32_t baudrate)
    : HwIfaceDescriptor(HW_IFACE_CAN),
      _deviceId(deviceId),
      _ifaceName(ifaceName),
      _baudrate(baudrate)
    {
    }
    virtual ~HwCanDescriptor(){}

    inline CanDevId GetCanDeviceId() const
    {
        return _deviceId; 
    }

    inline void SetCanDeviceId(IN CanDevId deviceId)
    {
        _deviceId = deviceId; 
    }

    inline uint32_t GetCanBaudrate() const
    {
        return _baudrate;
    }
    
    inline void SetCanBaudrate(IN uint32_t baudrate)
    {
        _baudrate = baudrate;
    }

    inline std::string GetCanIfaceName() const 
    {
        return _ifaceName;
    }

    inline void SetCanIfaceName(IN const std::string& ifaceName)
    {
        _ifaceName = ifaceName;
    }

private:

    CanDevId     _deviceId;
    std::string  _ifaceName;
    uint32_t     _baudrate;
};

class HwEthernetDescriptor: public HwIfaceDescriptor {
public:
    HwEthernetDescriptor(){}
    HwEthernetDescriptor(uint16_t deviceId, const std::string& ifaceName, const std::string& ip, uint32_t port)
    :HwIfaceDescriptor(HW_IFACE_ETH),
    _deviceId(deviceId),
    _ifaceName(ifaceName),
    _ip(ip),
    _port(port)
    {
    }
    virtual ~HwEthernetDescriptor(){}


    inline uint16_t GetDevId() const
    {
        return _deviceId;
    }
    inline void SetDevId(IN uint16_t deviceId)
    {
        _deviceId = deviceId;
    }

    inline std::string GetIfaceName() const
    { 
        return _ifaceName; 
    }

    inline void SetIfaceName(IN const std::string& ifaceName)
    {
        _ifaceName.assign(ifaceName); 
    }

    inline std::string GetIp() const
    { 
        return _ip; 
    }

    inline void SetIp(IN const std::string& ip)
    {
        _ip.assign(ip); 
    }

    inline uint32_t GetPort() const
    {
        return _port;
    }
    inline void SetPort(IN uint32_t port)
    {
        _port = port;
    }

private:
    uint16_t     _deviceId;
    std::string  _ifaceName;
    std::string  _ip;
    uint32_t     _port;
};

class HwRS485Descriptor: public HwIfaceDescriptor {
public:
    HwRS485Descriptor()
    {}
    HwRS485Descriptor(SerialDevId deviceId,
                      const std::string& ifaceName,
                      uint32_t baudrate)
    : HwIfaceDescriptor(HW_IFACE_RS485), 
     _deviceId(deviceId),
     _ifaceName(ifaceName),
     _baudrate(baudrate)
    {}
    virtual ~HwRS485Descriptor(){}

    inline std::string GetIfaceName() const
    {
        return _ifaceName; 
    }
    
    inline void SetIfaceName(IN const std::string&  ifaceName)
    {
        _ifaceName = ifaceName;
    }

    inline SerialDevId GetRs485DeviceId() const
    {
        return _deviceId;
    }

    inline void SetRs485DeviceId(IN SerialDevId deviceId)
    {
        _deviceId = deviceId;
    }

    inline uint32_t GetBaudrate() const
    {
        return _baudrate;
    }

    inline void SetBaudrate(IN uint32_t baudrate)
    {
        _baudrate = baudrate;    
    }

private:
    SerialDevId        _deviceId;
    std::string        _ifaceName;
    uint32_t           _baudrate;
};

class HwRegistry {
public:
    HwRegistry(HwIfaceType hwType)
    : _hwType(hwType)
    {}
    virtual ~HwRegistry()
    {}

    inline HwIfaceType GetHwType() const
    {
        return _hwType;    
    }
    inline void SetHwType(IN HwIfaceType hwType)
    {
        _hwType = hwType;
    }

private:
    HwIfaceType    _hwType;

};


class CanHwRegistry : public HwRegistry {
public:
    CanHwRegistry(const std::set<CanId>& ids, CanDevId deviceId)
     : HwRegistry(HW_IFACE_CAN),
       _ids(ids),
       _deviceId(deviceId)
    {}

    CanHwRegistry()
     : HwRegistry(HW_IFACE_CAN),
       _deviceId(0)
    {}

    virtual ~CanHwRegistry() 
    {}

    inline const std::set<CanId>& GetIds() const 
    {
        return _ids;
    }

    inline void SetIds(IN const std::set<CanId>& ids)
    {
        _ids = ids;    
    }

    inline CanDevId GetDevId() const
    {
        return _deviceId;    
    }

    inline void SetDevId(IN CanDevId deviceId) 
    {
        _deviceId = deviceId;
    }
    

private:
    
    std::set<CanId>          _ids;
    CanDevId                 _deviceId;

};

class Rs485HwRegistry : public HwRegistry {
public:
    Rs485HwRegistry(SerialDevId deviceId)
     : HwRegistry(HW_IFACE_RS485),
       _deviceId(deviceId)
    {}
    Rs485HwRegistry()
     : HwRegistry(HW_IFACE_RS485),
       _deviceId(0)
    {}
    virtual ~Rs485HwRegistry() 
    {}

    inline SerialDevId GetDevId() const
    {
        return _deviceId;    
    }

    inline void SetDevId(IN SerialDevId deviceId) 
    {
        _deviceId = deviceId;
    }
    

private:
    
    SerialDevId                 _deviceId;

};

class EthernetRegistry : public HwRegistry {
public:
    EthernetRegistry(const std::string& ip, uint32_t port, EthTransportType transType)
     : HwRegistry(HW_IFACE_ETH),
       _ip(ip),
       _port(port),
       _transType(transType)
    {}

    EthernetRegistry()
     : HwRegistry(HW_IFACE_ETH),
       _ip(""),
       _port(0),
       _transType(ETH_TRANSPORT_TYPE_UDP)
    {}



    virtual ~EthernetRegistry() 
    {}

    inline std::string GetIp() const
    {
        return _ip;    
    }

    inline void SetIp(IN const std::string& ip) 
    {
        _ip = ip;
    }
    
    inline uint32_t GetPort() const
    {
        return _port;    
    }

    inline void SetPort(IN uint32_t port) 
    {
        _port = port;
    }

    inline EthTransportType GetTransType() const
    {
        return _transType;    
    }

    inline void SetTransType(IN EthTransportType transType) 
    {
        _transType = transType;
    }
private:
    
    std::string                 _ip;
    uint32_t                    _port;
    EthTransportType            _transType;
};


}
}
#endif //OSAL_TYPES_H
