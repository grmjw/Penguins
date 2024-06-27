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

#ifndef EXTERNAL__EXTERNALTYPES_H_
#define EXTERNAL__EXTERNALTYPES_H_
#include <stdint.h>

#include <memory>
#include <set>
#include <string>

#ifdef _WIN32
#ifdef WIN_EXPORT_COM_LIB
#define EXPORT_COM_LIB __declspec(dllexport)
#else
#define EXPORT_COM_LIB __declspec(dllimport)
#endif
#else
#define EXPORT_COM_LIB __attribute__((visibility("default")))
#endif

#ifdef _WIN32
#ifdef WIN_EXPORT_SMART_ACCESS_LIB
#define EXPORT_SMART_ACCESS_LIB __declspec(dllexport)
#else
#define EXPORT_SMART_ACCESS_LIB __declspec(dllimport)
#endif
#else
#define EXPORT_SMART_ACCESS_LIB __attribute__((visibility("default")))
#endif

#ifdef _WIN32
#ifdef WIN_EXPORT_USER_INTERFACE_LIB
#define EXPORT_USER_INTERFACE_LIB __declspec(dllexport)
#else
#define EXPORT_USER_INTERFACE_LIB __declspec(dllimport)
#endif
#else
#define EXPORT_USER_INTERFACE_LIB __attribute__((visibility("default")))
#endif

#define IN
#define OUT
#define INOUT

namespace com {
namespace types {
typedef float float32_t;
typedef uint32_t ClientId;
typedef uint16_t PortId;
typedef uint8_t CanDevId;
typedef uint8_t SerialDevId;
typedef uint16_t CanId;

enum ErrorCode {
  ERROR_CODE_OK = 0,
  ERROR_CODE_SERIALIZATION_ERROR,
  ERROR_CODE_REGISTRATION_ERROR,
  ERROR_CODE_CLIENT_DISCONNECTED,
  ERROR_CODE_UNKNOWN_CLIENT,
  ERROR_CODE_UNKNOWN_LINK,
  ERROR_CODE_GENERIC_ERROR
};

enum ClientPhyLinkType {
  CLIENT_PHY_TYPE_CAN = 0,
  CLIENT_PHY_TYPE_ETH,
  CLIENT_PHY_TYPE_RS485,
  CLIENT_PHY_TYPE_UNKNOWN
};

enum SWUpdateStatus {
  RUNNING = 0,
  READY_SUCCESS,
  STOPPED_BY_MASTER,
  STOPPED_BY_SLAVE,
  STOPPED_BY_ERROR_TIMEOUT,
  STOPPED_BY_ERROR_BLOCK_REPEAT,
  STOPPED_BY_ERROR_IMAGE_INVALID,
  STOPPED_BY_ERROR_UNKNOWN,
  NOT_VALID
};

enum EthTransportType {
  ETH_TRANSPORT_TYPE_TCP,
  ETH_TRANSPORT_TYPE_UDP,
  ETH_TRANSPORT_TYPE_MULTICAST
};

class BufferDescriptor {
 public:
  BufferDescriptor(uint8_t* bufferPtr, size_t size)
      : _bufferPtr(bufferPtr), _size(size) {}

  BufferDescriptor() : _bufferPtr(nullptr), _size(0) {}

  ~BufferDescriptor() {}

  inline uint8_t* GetBufferPtr() const { return _bufferPtr; }

  inline size_t GetSize() const { return _size; }

  inline void SetBufferPtr(IN uint8_t* bufferPtr) { _bufferPtr = bufferPtr; }

  inline void SetSize(IN size_t size) { _size = size; }

 private:
  uint8_t* _bufferPtr;
  size_t _size;
};

class SWUpdateInfo {
 public:
  SWUpdateInfo()
      : _currentSegmentNumber(0),
        _currentDownloadedBytes(0),
        _updateState(NOT_VALID) {
    _currentImage.clear();
  }
  virtual ~SWUpdateInfo() {}

  inline uint64_t GetCurrentDownloadedBytes() const {
    return _currentDownloadedBytes;
  }

  inline void SetCurrentDownloadedBytes(uint64_t downloadedBytes) {
    _currentDownloadedBytes = downloadedBytes;
  }

  inline uint32_t GetCurrentSegmentNumber() const {
    return _currentSegmentNumber;
  }

  inline void SetCurrentSegmentNumber(uint32_t segment) {
    _currentSegmentNumber = segment;
  }

  inline std::string GetCurrentImage() const { return _currentImage; }

  inline void SetCurrentImage(std::string image) { _currentImage = image; }

  inline SWUpdateStatus GetUpdateStatus() const { return _updateState; }

  inline void SetUpdateStatus(SWUpdateStatus state) { _updateState = state; }

 private:
  uint32_t _currentSegmentNumber;
  uint64_t _currentDownloadedBytes;
  SWUpdateStatus _updateState;
  std::string _currentImage;
  // Downloaded Bytes from current Image-Segment
};

class ConnectedClientInfo {
 public:
  ConnectedClientInfo(ClientId id, ClientPhyLinkType phyType)
      : _clientId(id), _phyLinkType(phyType) {}

  virtual ~ConnectedClientInfo() {}

  inline ClientId GetConnectedClientId() const { return _clientId; }

  inline ClientPhyLinkType GetPhyLinkType() const { return _phyLinkType; }

 private:
  ClientId _clientId;
  ClientPhyLinkType _phyLinkType;
};

}  // namespace types
}  // namespace com
#endif  // EXTERNAL__EXTERNALTYPES_H_
