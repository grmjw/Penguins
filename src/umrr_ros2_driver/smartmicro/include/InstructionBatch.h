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

#ifndef EXTERNAL__INSTRUCTIONBATCH_H_
#define EXTERNAL__INSTRUCTIONBATCH_H_

#include <ExternalTypes.h>
#include <Instruction.h>

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace com {
namespace common {
class Instruction;

namespace uif {
class InstructionEntry;
class UserInterface;
}  // namespace uif
}  // namespace common

namespace master {
class InstructionIf;

typedef std::pair<std::string, std::string> InstKey;

template <typename T>
inline bool validateDataType(IN std::shared_ptr<InstructionIf> inst) {
  return false;
}

template <>
inline bool validateDataType<int8_t>(IN std::shared_ptr<InstructionIf> inst) {
  return inst->GetDataType() == DATA_TYPE_I8;
}

template <>
inline bool validateDataType<uint8_t>(IN std::shared_ptr<InstructionIf> inst) {
  return (inst->GetDataType() == DATA_TYPE_U8);
}

template <>
inline bool validateDataType<int16_t>(IN std::shared_ptr<InstructionIf> inst) {
  return inst->GetDataType() == DATA_TYPE_I16;
}

template <>
inline bool validateDataType<uint16_t>(IN std::shared_ptr<InstructionIf> inst) {
  return inst->GetDataType() == DATA_TYPE_U16;
}

template <>
inline bool validateDataType<int32_t>(IN std::shared_ptr<InstructionIf> inst) {
  return inst->GetDataType() == DATA_TYPE_I32;
}

template <>
inline bool validateDataType<uint32_t>(IN std::shared_ptr<InstructionIf> inst) {
  return inst->GetDataType() == DATA_TYPE_U32;
}

template <>
inline bool validateDataType<float>(IN std::shared_ptr<InstructionIf> inst) {
  return inst->GetDataType() == DATA_TYPE_F32;
}

class EXPORT_SMART_ACCESS_LIB ResponseBatch {
 public:
  ResponseBatch();
  ~ResponseBatch();

  bool AddResponse(IN std::shared_ptr<InstructionIf> inst);

  template <typename T>
  bool GetResponse(IN const std::string &sectionName,
                   IN const std::string &instName,
                   OUT std::vector<std::shared_ptr<Response<T>>> &result) {
    std::vector<std::shared_ptr<InstructionIf>> instructions;
    bool retVal = getAllInstByName(sectionName, instName, instructions);
    if (retVal) {
      for (auto &inst : instructions) {
        if (retVal) {
          if (validateDataType<T>(inst)) {
            result.push_back(std::dynamic_pointer_cast<Response<T>>(inst));
          } else {
            result.clear();
            retVal = false;
          }
        }
      }
    }
    return retVal;
  }

 private:
  bool getAllInstByName(
      IN const std::string &sectionName, IN const std::string &instName,
      OUT std::vector<std::shared_ptr<InstructionIf>> &result);

  typedef std::multimap<InstKey, std::shared_ptr<InstructionIf>> ResponseMap;

  ResponseMap _responseMap;
};

typedef std::function<void(com::types::ClientId,
                           std::shared_ptr<ResponseBatch>)>
    ResponseCallback;

class EXPORT_SMART_ACCESS_LIB InstructionBatch {
 public:
  virtual ~InstructionBatch();

  bool AddRequest(IN std::shared_ptr<InstructionIf> inst);

  inline uint32_t GetId() const { return _batchId; }

  inline com::types::ClientId GetClientId() const { return _clientId; }

  inline uint8_t GetNumberOfInstructions() const { return _cntInstructions; }

  inline uint8_t GetMaxNumberOfInstructions() const { return _maxNumberInst; }

  InstructionBatch(const InstructionBatch &) = delete;
  void operator=(const InstructionBatch) = delete;

 protected:
  InstructionBatch(
      IN uint32_t batchId, IN com::types::ClientId clientId,
      IN std::shared_ptr<com::common::uif::UserInterface> userIface,
      IN uint8_t maxNumInst);

 private:
  friend class InstructionService;

  com::types::ErrorCode send(IN ResponseCallback callback);

  bool addInstruction(
      IN std::shared_ptr<InstructionIf> request,
      IN std::shared_ptr<com::common::uif::InstructionEntry> entry,
      OUT std::shared_ptr<com::common::Instruction> &inst);

  void setRequest(IN RequestType type,
                  INOUT std::shared_ptr<com::common::Instruction> inst);

  bool addResponse(IN std::shared_ptr<InstructionIf> inst, IN uint64_t value,
                   IN ResponseType response, IN DataType dataType,
                   INOUT std::shared_ptr<ResponseBatch> respBatch);

  template <typename T>
  void addResponseToBatch(IN std::shared_ptr<InstructionIf> inst,
                          IN uint64_t value, IN ResponseType response,
                          INOUT std::shared_ptr<ResponseBatch> respBatch);

  typedef std::vector<std::shared_ptr<InstructionIf>> InstructionVec;

  InstructionVec _instructions;
  uint32_t _batchId;
  com::types::ClientId _clientId;
  std::shared_ptr<com::common::uif::UserInterface> _userIface;
  ResponseCallback _callback;
  uint8_t _maxNumberInst;
  uint8_t _cntInstructions;
};

}  // namespace master
}  // namespace com

#endif  // EXTERNAL__INSTRUCTIONBATCH_H_
