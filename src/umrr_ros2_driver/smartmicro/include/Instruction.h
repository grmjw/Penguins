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

#ifndef EXTERNAL__INSTRUCTION_H_
#define EXTERNAL__INSTRUCTION_H_

#include <ExternalTypes.h>

#include <memory>
#include <set>
#include <string>
#include <type_traits>

namespace com {
namespace master {
enum DataType {
  DATA_TYPE_I8 = 1,  /**< @brief Signed integer 8 bit. */
  DATA_TYPE_U8 = 2,  /**< @brief Unsigned integer 8 bit. */
  DATA_TYPE_I16 = 3, /**< @brief Signed integer 16 bit. */
  DATA_TYPE_U16 = 4, /**< @brief Unsigned integer 16 bit. */
  DATA_TYPE_I32 = 5, /**< @brief Signed integer 32 bit. */
  DATA_TYPE_U32 = 6, /**< @brief Unsigned integer 32 bit. */
  DATA_TYPE_F32 = 7, /**< @brief IEEE float 32 bit. */
  DATA_TYPE_UNKNOWN = 8
};

enum RequestType {
  REQUEST_TYPE_SET_PARAM = 0,
  REQUEST_TYPE_GET_PARAM = 1,
  REQUEST_TYPE_GET_STATUS = 2,
  REQUEST_TYPE_CMD = 3
};

enum ResponseType {
  RESPONSE_NO_RESPONSE = 0U, /**< @brief No instruction Response */
  RESPONSE_SUCCESS =
      1U, /**< @brief Instruction Response was processed successfully */
  RESPONSE_ERROR = 2U,         /**< @brief General error */
  RESPONSE_ERROR_REQUEST = 3U, /**< @brief Invalid request */
  RESPONSE_ERROR_SECTION = 4U, /**< @brief Invalid section */
  RESPONSE_ERROR_ID = 5U,      /**< @brief Invalid id */
  RESPONSE_ERROR_PROT = 6U,    /**< @brief Invalid protection */
  RESPONSE_ERROR_MIN = 7U,     /**< @brief Value out of minimal bounds */
  RESPONSE_ERROR_MAX = 8U,     /**< @brief Value out of maximal bounds */
  RESPONSE_ERROR_NAN = 9U,     /**< @brief Value is not a number */
  RESPONSE_ERROR_TYPE = 10U,   /**< @brief Type of Instruction is not valid */
  RESPONSE_ERROR_DIM = 11U,    /**< @brief Dim of Instruction is not valid */
  RESPONSE_ERROR_ELEMENT =
      12U, /**< @brief Element of Instruction is not valid */
  RESPONSE_ERROR_SIGNATURE =
      13U, /**< @brief Signature of Instruction is not valid */
  RESPONSE_ERROR_ACCESS_LVL = 14U /**< @brief Access level is not valid */
};

class EXPORT_SMART_ACCESS_LIB InstructionIf {
 public:
  InstructionIf() {}
  virtual ~InstructionIf() {}

  virtual bool GetConvertValue(OUT uint64_t &result) = 0;

  virtual std::string GetSectionName() const = 0;

  virtual std::string GetInstructionName() const = 0;

  virtual RequestType GetRequestType() const = 0;

  virtual uint16_t GetFirstDimIdx() const = 0;

  virtual uint16_t GetSecondDimIdx() const = 0;

  virtual DataType GetDataType() const = 0;

  bool operator==(InstructionIf &rhs) {
    return ((GetSectionName() == rhs.GetSectionName()) &&
            (GetInstructionName() == rhs.GetInstructionName()) &&
            (GetFirstDimIdx() == rhs.GetFirstDimIdx()) &&
            (GetSecondDimIdx() == rhs.GetSecondDimIdx()));
  }
};

template <typename T>
inline bool RertrieveDataType(OUT DataType &type) {
  return false;
}

template <>
inline bool RertrieveDataType<int8_t>(OUT DataType &type) {
  type = DATA_TYPE_I8;
  return true;
}

template <>
inline bool RertrieveDataType<uint8_t>(OUT DataType &type) {
  type = DATA_TYPE_U8;
  return true;
}

template <>
inline bool RertrieveDataType<int16_t>(OUT DataType &type) {
  type = DATA_TYPE_I16;
  return true;
}

template <>
inline bool RertrieveDataType<uint16_t>(OUT DataType &type) {
  type = DATA_TYPE_U16;
  return true;
}

template <>
inline bool RertrieveDataType<int32_t>(OUT DataType &type) {
  type = DATA_TYPE_I32;
  return true;
}

template <>
inline bool RertrieveDataType<uint32_t>(OUT DataType &type) {
  type = DATA_TYPE_U32;
  return true;
}

template <>
inline bool RertrieveDataType<float>(OUT DataType &type) {
  type = DATA_TYPE_F32;
  return true;
}

template <typename T>
class EXPORT_SMART_ACCESS_LIB InstructionBase : public InstructionIf {
 public:
  InstructionBase(RequestType request, const std::string &sectionName,
                  const std::string &instName, T value)
      : _request(request),
        _sectionName(sectionName),
        _instName(instName),
        _value(value),
        _firstDimIdx(0),
        _secondDimIdx(0),
        _dataType(DATA_TYPE_UNKNOWN) {
    RertrieveDataType<T>(_dataType);
  }

  InstructionBase(RequestType request, const std::string &sectionName,
                  const std::string &instName, T value, uint16_t firstDimIdx,
                  uint16_t secondDimIdx)
      : _request(request),
        _sectionName(sectionName),
        _instName(instName),
        _value(value),
        _firstDimIdx(firstDimIdx),
        _secondDimIdx(secondDimIdx),
        _dataType(DATA_TYPE_UNKNOWN) {
    RertrieveDataType<T>(_dataType);
  }

  virtual ~InstructionBase() {}

  virtual bool GetConvertValue(OUT uint64_t &result) {
    bool retVal = false;
    if (std::is_trivial<T>::value && !std::is_class<T>::value) {
      if (std::is_floating_point<T>::value) {
        float tmp = _value;
        uint64_t *rawIntPointer = reinterpret_cast<uint64_t *>(&tmp);
        result = *rawIntPointer;
        result &= 0xFFFFFFFF;

      } else {
        result = (uint64_t)(_value);
      }
      retVal = RertrieveDataType<T>(_dataType);
    }
    return retVal;
  }

  virtual std::string GetSectionName() const { return _sectionName; }

  virtual std::string GetInstructionName() const { return _instName; }

  virtual RequestType GetRequestType() const { return _request; }

  virtual uint16_t GetFirstDimIdx() const { return _firstDimIdx; }

  virtual uint16_t GetSecondDimIdx() const { return _secondDimIdx; }

  virtual DataType GetDataType() const { return _dataType; }

  T GetValue() const { return _value; }

 private:
  RequestType _request;
  std::string _sectionName;
  std::string _instName;
  T _value;
  uint16_t _firstDimIdx;
  uint16_t _secondDimIdx;
  DataType _dataType;
};

template <typename T>
class EXPORT_SMART_ACCESS_LIB Request : public InstructionBase<T> {
 public:
  Request(RequestType request, const std::string &sectionName,
          const std::string &instName, T value)
      : InstructionBase<T>(request, sectionName, instName, value) {}

  Request(RequestType request, const std::string &sectionName,
          const std::string &instName, T value, uint16_t firstDimIdx,
          uint16_t secondDimIdx)
      : InstructionBase<T>(request, sectionName, instName, value, firstDimIdx,
                           secondDimIdx) {}
  virtual ~Request() {}
};

template <typename T>
class EXPORT_SMART_ACCESS_LIB Response : public InstructionBase<T> {
 public:
  Response()
      : InstructionBase<T>(REQUEST_TYPE_SET_PARAM, "", "", 0),
        _response(RESPONSE_NO_RESPONSE) {}

  Response(RequestType request, ResponseType response,
           const std::string &sectionName, const std::string &instName, T value)
      : InstructionBase<T>(request, sectionName, instName, value),
        _response(response) {}
  Response(RequestType request, ResponseType response,
           const std::string &sectionName, const std::string &instName, T value,
           uint16_t firstDimIdx, uint16_t secondDimIdx)
      : InstructionBase<T>(request, sectionName, instName, value, firstDimIdx,
                           secondDimIdx),
        _response(response) {}

  Response(RequestType request, const std::string &sectionName,
           const std::string &instName, T value, ResponseType response,
           uint16_t firstDimIdx, uint16_t secondDimIdx)
      : InstructionBase<T>(request, sectionName, instName, value, firstDimIdx,
                           secondDimIdx),
        _response(response) {}

  Response(std::shared_ptr<Request<T>> &request, T value, ResponseType response)
      : InstructionBase<T>(request->GetRequestType(), request->GetSectionName(),
                           request->GetInstructionName(), value,
                           request->GetFirstDimIdx(),
                           request->GetSecondDimIdx()),
        _response(response) {}

  virtual ~Response() {}

  inline ResponseType GetResponseType() const { return _response; }

 private:
  ResponseType _response;
};

template <typename T>
class EXPORT_SMART_ACCESS_LIB SetParamRequest : public Request<T> {
 public:
  SetParamRequest(const std::string &sectionName, const std::string &instName,
                  T value)
      : Request<T>(REQUEST_TYPE_SET_PARAM, sectionName, instName, value) {}

  SetParamRequest(const std::string &sectionName, const std::string &instName,
                  T value, uint16_t firstDimIdx, uint16_t secondDimIdx)
      : Request<T>(REQUEST_TYPE_SET_PARAM, sectionName, instName, value,
                   firstDimIdx, secondDimIdx) {}

  virtual ~SetParamRequest() {}
};

template <typename T>
class EXPORT_SMART_ACCESS_LIB GetParamRequest : public Request<T> {
 public:
  GetParamRequest(const std::string &sectionName, const std::string &instName)
      : Request<T>(REQUEST_TYPE_GET_PARAM, sectionName, instName, 0) {}

  GetParamRequest(const std::string &sectionName, const std::string &instName,
                  uint16_t firstDimIdx, uint16_t secondDimIdx)
      : Request<T>(REQUEST_TYPE_GET_PARAM, sectionName, instName, 0,
                   firstDimIdx, secondDimIdx) {}
  virtual ~GetParamRequest() {}
};

template <typename T>
class EXPORT_SMART_ACCESS_LIB GetStatusRequest : public Request<T> {
 public:
  GetStatusRequest(const std::string &sectionName, const std::string &instName)
      : Request<T>(REQUEST_TYPE_GET_STATUS, sectionName, instName, 0) {}

  GetStatusRequest(const std::string &sectionName, const std::string &instName,
                   uint16_t firstDimIdx, uint16_t secondDimIdx)
      : Request<T>(REQUEST_TYPE_GET_STATUS, sectionName, instName, 0,
                   firstDimIdx, secondDimIdx) {}
  virtual ~GetStatusRequest() {}
};

class EXPORT_SMART_ACCESS_LIB CmdRequest : public Request<uint32_t> {
 public:
  CmdRequest(const std::string &sectionName, const std::string &instName,
             uint32_t value)
      : Request<uint32_t>(REQUEST_TYPE_CMD, sectionName, instName, value) {}

  virtual ~CmdRequest() {}
};
}  // namespace master
}  // namespace com

#endif  // EXTERNAL__INSTRUCTION_H_
