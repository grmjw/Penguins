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

#ifndef EXTERNAL__INSTRUCTIONSERVICEIFACE_H_
#define EXTERNAL__INSTRUCTIONSERVICEIFACE_H_

#include <ExternalTypes.h>
#include <Instruction.h>
#include <InstructionBatch.h>
#include <VersionedIface.h>

#include <functional>
#include <memory>
#include <set>

namespace com {
namespace master {
class EXPORT_SMART_ACCESS_LIB InstructionServiceIface
    : public com::VersionedIface {
 public:
  InstructionServiceIface() {}
  virtual ~InstructionServiceIface() {}

  /*
   * Function: Get()
   * Arguments: none
   * Return: std::shared_ptr<InstructionServiceIface>
   * Description: Returns a singletone instance of a this class, since this is
   * only an abstract class, the instantiation should be done by a deriving
   * class.
   */
  static std::shared_ptr<InstructionServiceIface> Get();

  /*
   * Function: Init
   * Arguments: none
   * Return: bool
   * Description: Initializes the instruction services layer.
   */
  virtual bool Init() = 0;
  /*
   * Function: AllocateInstructionBatch
   * Arguments: IN ClientId clientId id of the client
   *            OUT std::shared_ptr<InstructionBatch>& allocated instruction
   * batch Return : true if allocation was successful, false if client's user
   * interface is unknown Description: Allocates a new instruction batch, only
   * allocated batches shall be used
   */
  virtual bool AllocateInstructionBatch(
      IN com::types::ClientId clientId,
      OUT std::shared_ptr<InstructionBatch>& batch) = 0;
  /*
   * Function: ReleaseInstructionBatch
   * Arguments: std::shared_ptr<InstructionBatch> InstructionBatch to release
   * Return:  ErrorCode
   * Description: Releases InstructionBatch, the pointer shall not be used after
   * that
   */

  virtual com::types::ErrorCode ReleaseInstructionBatch(
      IN std::shared_ptr<InstructionBatch> instBatch) = 0;

  /*
   * Function: SendInstructionBatch
   * Arguments:std::shared_ptr<InstructionBatch> - Batch of Instructions
   *           ResponseCallback  - Callback , which we be called upon receiveing
   * response. Return: ErrorCode Description: Sends batch of instruction to the
   * given list of clients
   */

  virtual com::types::ErrorCode SendInstructionBatch(
      IN std::shared_ptr<InstructionBatch>, IN ResponseCallback) = 0;
};

}  // namespace master
}  // namespace com

#endif  // EXTERNAL__INSTRUCTIONSERVICEIFACE_H_
