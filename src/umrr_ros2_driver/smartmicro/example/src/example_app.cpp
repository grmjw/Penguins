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

#include <CommunicationServicesIface.h>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>

using namespace com::common;
using namespace com::master;
using namespace com::types;

// Global variables and functions
std::mutex deviceMonMutex;
std::condition_variable deviceMonVariable;
ClientId Client01Id;
bool Client01Connected = false;
bool DeviceMonStarted = false;

std::atomic<bool> RunFlag(true);
bool softwareInfoDispatched = false;
bool softwareVersionDispatched = false;
uint64_t secondsToMicroSeconds = 1000000;
uint64_t max32Bit = 4294967295;
uint64_t shift32 = 32;

void MyResponseVersionCallback(IN ClientId clientId,
                               IN std::shared_ptr<ResponseBatch> response) {
  // Check for response for software_info request
  std::vector<std::shared_ptr<Response<uint16_t>>> mySoftwareInfoResp;
  if (response->GetResponse<uint16_t>("software_info", "software_info_version",
                                      mySoftwareInfoResp)) {
    for (auto &resp : mySoftwareInfoResp) {
      uint16_t value = resp->GetValue();
      std::cout << "Response to SoftwareInfo-Request: SoftwareInfoVersion = "
                << value << std::endl;
    }
    softwareInfoDispatched = true;
  }
  std::vector<std::shared_ptr<Response<uint16_t>>> mySoftwareVersion1Resp;
  if (response->GetResponse<uint16_t>("software_info", "software_version_1",
                                      mySoftwareVersion1Resp)) {
    for (auto &resp : mySoftwareVersion1Resp) {
      uint16_t value = resp->GetValue();
      std::cout << "Response to SoftwareInfo-Request: SoftwareVersion1 = "
                << value << std::endl;
    }
    softwareVersionDispatched = true;
  }
  if (softwareInfoDispatched && softwareVersionDispatched) {
    // Responses for triggered Instruction-Requests are dispatched
    // With using BaseUserInterface we can't so far receive any DataService
    // Responsesso we can terminate the example_app now
    RunFlag.store(false);
  }
}

void MyResponsePseudoCallback(IN ClientId clientId,
                              IN std::shared_ptr<ResponseBatch> response) {
  // Check for response for setting someParam1
  // Value of 2-Dim-Parameter 'some_parameter_2' in 'some_section_2'
  std::vector<std::shared_ptr<Response<uint8_t>>> mySomeParamResp2;
  if (response->GetResponse<uint8_t>("some_section_2", "some_parameter_2",
                                     mySomeParamResp2)) {
    for (auto &resp : mySomeParamResp2) {
      uint16_t index1 = resp->GetFirstDimIdx();
      uint16_t index2 = resp->GetSecondDimIdx();
      uint8_t value = resp->GetValue();
      std::cout << "Value[" << index1 << "][" << index2 << "] = " << value
                << std::endl;
    }
  }
  // Check for response for getting someParam2
  // Value of 1-Dim-Parameter 'some_parameter_3' in 'some_section_3'
  std::vector<std::shared_ptr<Response<uint8_t>>> mySomeParamResp3;
  if (response->GetResponse<uint8_t>("some_section_3", "some_parameter_3",
                                     mySomeParamResp3)) {
    for (auto &resp : mySomeParamResp3) {
      uint8_t value = resp->GetValue();
      std::cout << "Value = " << value << std::endl;
    }
  }
}

void MyResponseCmdCallback(IN ClientId clientId,
                           IN std::shared_ptr<ResponseBatch> response) {
  // Check for response for setting command
  std::vector<std::shared_ptr<Response<uint32_t>>> mySomeCmdResp;
  if (response->GetResponse<uint32_t>("some_command_section", "some_command",
                                      mySomeCmdResp)) {
    for (auto &resp : mySomeCmdResp) {
      uint32_t value = resp->GetValue();
      std::cout << "Command Response Value  = " << value << std::endl;
    }
  }
}

void MyConnectedInfoCallback(ClientId Id, bool clientStatus) {
  if (clientStatus) {
    std::cout << "MyConnectedInfoCallback(): ClientId = 0x" << std::hex << Id
              << " is connected." << std::endl;
    if (Id == Client01Id) {
      Client01Connected = true;
    }
  } else {
    std::cout << "MyConnectedInfoCallback(): Client01 = 0x" << std::hex << Id
              << " is disconnected." << std::endl;
    if (Id == Client01Id) {
      Client01Connected = false;
    }
  }
}

void MyDeviceMonitorThreadFkt() {
  // Wait until main() has started the monitoring of new connections
  std::unique_lock<std::mutex> deviceMonLock(deviceMonMutex);
  deviceMonVariable.wait(deviceMonLock, [] { return DeviceMonStarted; });

  // We own the deviceMonLock and can observe Flag 'Client01Connected'
  int counter = 0;
  while ((Client01Connected == false) && (counter < 60)) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    counter++;
  }

  // Manual unlocking the deviceMonLock
  deviceMonLock.unlock();
  // Notification that DeviceMonitorThread is ready
  deviceMonVariable.notify_one();
}

bool MyGetRefTimeCallback(uint64_t &time) {
  auto timestamp = std::chrono::system_clock::now();
  uint64_t microSinceEpoch =
      std::chrono::duration_cast<std::chrono::microseconds>(
          timestamp.time_since_epoch())
          .count();
  uint64_t secSinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(
                               timestamp.time_since_epoch())
                               .count();
  // Get time below one second
  uint64_t usTimestamp = (microSinceEpoch) % secondsToMicroSeconds;
  // Calculate 32bit NTP fraction field
  uint64_t ntpTimestampFrac = (usTimestamp * max32Bit) / secondsToMicroSeconds;
  time = (secSinceEpoch << shift32) + ntpTimestampFrac;
  return true;
}

bool StartTimeSyncMasterService(
    std::shared_ptr<TimeSyncMasterIface> timeSyncMaster) {
  if (ERROR_CODE_OK != timeSyncMaster->RegisterRefTimeCallback(std::bind(
                           &MyGetRefTimeCallback, std::placeholders::_1))) {
    std::cout << "Failed to register ref time callback" << std::endl;
    return false;
  }

  if (ERROR_CODE_OK != timeSyncMaster->Start()) {
    std::cout << "Failed to start time sync master service" << std::endl;
    return false;
  }

  /* For each slave, that participate at time synchronization shall be allocated
  a slave id. This id shall be added also on the master side: if(ERROR_CODE_OK
  != timeSyncMaster->AddSlave(0))
  {
      std::cout << "Failed to add slave id 0" << std::endl;
      return false;
  }*/

  return true;
}

/*******************************************************************************************
 ***
 ***     int main(int argc, char *argv[])
 ***
 ***     Remark: - First Argument must contain the ClientId
 ***             - If ClientId is given in hex-Format the string must lead with
 *'0x' identifier
 ***
 *******************************************************************************************/
int main(int argc, char *argv[]) {
  // Check the given Argument for ClientId
  ClientId clientId;
  if (argc != 2) {
    std::cout << "Specifiy usable ClientId as command line argument"
              << std::endl;
    return 1;
  } else {
    std::string clientIdStr(argv[1]);
    if (clientIdStr.compare(0, 2, "0x") == 0) {
      // Found ClientId as Hex-String"
      std::string::size_type clientIdHexStrLen;
      int32_t result = 0;
      try {
        result = std::stoi(clientIdStr, &clientIdHexStrLen, 0);
        clientId = (ClientId)result;
      }
      // Check for invalid argument in stoi-Call
      // so that call has thrown a related exception
      catch (std::invalid_argument const &invalidArg) {
        std::cout << "Error in HexConversion-Call: " << invalidArg.what()
                  << std::endl;
        return 1;
      }
    } else {
      // Found ClientId as int-String"
      clientId = std::stoul(clientIdStr, nullptr, 10);
    }
    Client01Id = clientId;
    std::cout << "Use ClientId = 0x" << std::hex << Client01Id
              << " in communication services" << std::endl;
  }

  // Create and initialize CommunicationServices
  std::shared_ptr<CommunicationServicesIface> services =
      CommunicationServicesIface::Get();
  if (!services->Init()) {
    std::cout << "Init failed" << std::endl;
    return 1;
  }

  // Start TimeSyncProcedure -----------------------------------------------
  std::shared_ptr<TimeSyncMasterIface> timeSyncMaster =
      services->GetTimeSyncServiceIface()->GetMasterService();
  if (!StartTimeSyncMasterService(timeSyncMaster)) {
    std::cout << "Failed to start time sync master service" << std::endl;
  }

  // Sensor availabilty check -----------------------------------------------
  // Check if current client is actually in list of connected clients
  // Get DeviceMonitor-Service
  std::shared_ptr<DeviceMonitorServiceIface> deviceMonitorService =
      services->GetDeviceMonitorService();
  if (deviceMonitorService->RegisterConnectedClientCallback(
          MyConnectedInfoCallback) != ERROR_CODE_OK) {
    std::cout << "Registering ConnectedClientCallback failed" << std::endl;
    std::cout << "Application " << argv[0] << " exited" << std::endl;
    timeSyncMaster->Stop();
    return 1;
  }
  // Get Client-List of current connected Devices
  std::vector<ConnectedClientInfo> clientInfoVector;
  if (deviceMonitorService->GetConnectedClientInfo(clientInfoVector)) {
    if (clientInfoVector.empty() == false) {
      std::vector<ConnectedClientInfo>::iterator it;
      for (it = clientInfoVector.begin(); it != clientInfoVector.end(); ++it) {
        if (it->GetConnectedClientId() == Client01Id) {
          std::cout << "ClientID = 0x" << std::hex << Client01Id
                    << " is connected and ready to use" << std::endl;
          Client01Connected = true;
          break;
        }
      }
    }
    // Connection-Monitoring until connection is available or timeout expired
    if (!Client01Connected) {
      std::cout << "Wait for connections ..." << std::endl;
      // Run DeviceMonitorThread
      std::thread DeviceMonitorThread(MyDeviceMonitorThreadFkt);

      // Start the monitoring of new connections
      // Set Flag 'DeviceMonStarted' after owning the unique_lock
      {
        std::lock_guard<std::mutex> deviceMonLock(deviceMonMutex);
        DeviceMonStarted = true;
      }
      // Send Start-Notification to DeviceMonitorThread
      deviceMonVariable.notify_one();

      // Wait for DeviceMonitorThread for finding connection
      {
        std::chrono::milliseconds relativeTimeout(3000);
        std::unique_lock<std::mutex> deviceMonLock(deviceMonMutex);
        if (deviceMonVariable.wait_for(deviceMonLock, relativeTimeout,
                                       [] { return Client01Connected; })) {
          std::cout << "ClientID = 0x" << std::hex << Client01Id
                    << " is connected and ready to use" << std::endl;
        } else {
          std::cout << "DeviceMonitorThread timed out" << std::endl;
        }
      }

      // Wait until DeviceMonitorThread has finished running
      DeviceMonitorThread.join();
      if (!Client01Connected) {
        std::cout << "No connection for ClientID = 0x" << std::hex << Client01Id
                  << " possible - Application " << argv[0] << " exited"
                  << std::endl;
        timeSyncMaster->Stop();
        return 1;
      }
    }
  } else {
    std::cout << "Error - getting ClientInfo-List of connected Devices failed"
              << std::endl;
    std::cout << "Application " << argv[0] << " exited" << std::endl;
    timeSyncMaster->Stop();
    return 1;
  }

  // Prepare Instructions and send requests to Client
  std::shared_ptr<InstructionServiceIface> inst(
      services->GetInstructionService());
  /*------------------------------------------------------------------------
    ---   Easy example for handling InstructionBatch
    ---   Prepare request for getting software_info_version
    -----------------------------------------------------------------------*/
  // Allocating instruction batch for the given sensor client id
  std::shared_ptr<InstructionBatch> batchStatus;
  if (!inst->AllocateInstructionBatch(Client01Id, batchStatus)) {
    std::cout << "Allocate Instruction Batch failed" << std::endl;
    std::cout << "Application " << argv[0] << " exited" << std::endl;
    timeSyncMaster->Stop();
    return 1;
  }
  // GET STATUS Instruction: Create instruction for getting
  // softwarcde_info_version from section software_info
  std::shared_ptr<GetStatusRequest<uint16_t>> status(
      new GetStatusRequest<uint16_t>("software_info", "software_info_version"));
  // GET STATUS Instruction: Create instruction for getting
  // bootloader_info_version from section bootloader_info
  std::shared_ptr<GetStatusRequest<uint16_t>> status02(
      new GetStatusRequest<uint16_t>("software_info", "software_version_1"));

  // Add instructions to batch
  if (!batchStatus->AddRequest(status)) {
    std::cout << "Failed to add instruction for softwareInfoVersion to batch"
              << std::endl;
  }
  if (!batchStatus->AddRequest(status02)) {
    std::cout << "Failed to add instruction for softwareVersion_1 to batch"
              << std::endl;
  }
  // Send instruction batch to the device
  if (ERROR_CODE_OK != inst->SendInstructionBatch(
                           batchStatus, std::bind(&MyResponseVersionCallback,
                                                  std::placeholders::_1,
                                                  std::placeholders::_2))) {
    std::cout << "Error - sending Request for getting SW-Info and "
                 "SW-Version_1-Info failed"
              << std::endl;
  } else {
    std::cout
        << "Request for getting SW-Info and SW-Version_1-Info successfully sent"
        << std::endl;
  }

  /*------------------------------------------------------------------------
    ---   Second example for handling more complex InstructionBatch
    ---   Prepare request for getting "some_status_1"
    ---   Prepare request for setting 2-dim-Parameter "some_parameter_2"
    ---   Prepare request for getting 1-dim-Parameter some_parameter_3"
    ---   Hint: These requests are "Pseudo-Instructions" which describe
    ---         the handling but are not part of any real User-Interface
    -----------------------------------------------------------------------*/
  // Next allocation of instruction batch for the given sensor client id
  std::shared_ptr<InstructionBatch> batchParam;
  if (!inst->AllocateInstructionBatch(Client01Id, batchParam)) {
    std::cout << "Second allocation of Instruction-Batch failed" << std::endl;
    std::cout << "Application " << argv[0] << " exited" << std::endl;
    timeSyncMaster->Stop();
    return 1;
  }
  // SET PARAM: Create instruction for setting parameter
  std::shared_ptr<SetParamRequest<uint8_t>> someParam1(
      new SetParamRequest<uint8_t>("some_section_2",   /* section name   */
                                   "some_parameter_2", /* parameter name */
                                   1, /* value                    */
                                   1, /* dimension 1              */
                                   0  /* dimension 2              */
                                   ));
  // GET PARAM: Create instruction for getting parameter
  std::shared_ptr<GetParamRequest<uint8_t>> someParam2(
      new GetParamRequest<uint8_t>("some_section_3",  /* section name  */
                                   "some_parameter_3" /* parameter name */
                                   ));
  if (!batchParam->AddRequest(someParam1)) {
    std::cout
        << "Failed to add instruction for setting someParam1 to paramBatch"
        << std::endl;
  }
  if (!batchParam->AddRequest(someParam2)) {
    std::cout << "Failed to add instruction for getting value of someParam2 to "
                 "paramBatch"
              << std::endl;
    std::cout << "Reason: Pseudo-ParameterInstructions don't match with "
                 "User-Interface."
              << std::endl;
  }
  // Send instruction batch to the device
  if (ERROR_CODE_OK != inst->SendInstructionBatch(
                           batchParam, std::bind(&MyResponsePseudoCallback,
                                                 std::placeholders::_1,
                                                 std::placeholders::_2))) {
    std::cout << "SendInstructionBatch() failed cause paramBatch is empty."
              << std::endl;
  }

  /*------------------------------------------------------------------------
    ---   Example for Command API
    ------------------------------------------------------------------------*/
  std::shared_ptr<InstructionBatch> batchCmd;
  if (!inst->AllocateInstructionBatch(Client01Id, batchCmd)) {
    std::cout << "Third allocation of Instruction-Batch failed" << std::endl;
    std::cout << "Application " << argv[0] << " exited" << std::endl;
    timeSyncMaster->Stop();
    return 1;
  }
  std::shared_ptr<CmdRequest> someCmd(new CmdRequest(
      "some_command_section", /* section name      */
      "some_command",         /* command name      */
      1                       /* value             */
      ));
  if (!batchCmd->AddRequest(someCmd)) {
    std::cout << "Failed to add Pseudo-Command to commandBatch" << std::endl;
    std::cout << "Reason: Pseudo-CommandInstruction doesn't match with "
                 "User-Interface."
              << std::endl;
  }

  if (ERROR_CODE_OK !=
      inst->SendInstructionBatch(
          batchCmd, std::bind(&MyResponseCmdCallback, std::placeholders::_1,
                              std::placeholders::_2))) {
    std::cout << "SendInstructionBatch() failed cause commandBatch is empty."
              << std::endl;
  }

  /*----------------------------------------------------------------------------
    ---  Wait for Response-Callbacks
    ---------------------------------------------------------------------------*/
  std::cout << "Wait for Response-Callbacks..." << std::endl;
  while (RunFlag.load()) {
  }

  /*----------------------------------------------------------------------------
    ---  Release all allocated InstructionBatches
    ---  after all expected responses are dispatched
    ---------------------------------------------------------------------------*/
  if (ERROR_CODE_OK != inst->ReleaseInstructionBatch(batchStatus)) {
    std::cout << "Error: Could not release batchStatus" << std::endl;
  }
  if (ERROR_CODE_OK != inst->ReleaseInstructionBatch(batchParam)) {
    std::cout << "Error: Could not release batchParam" << std::endl;
  }
  if (ERROR_CODE_OK != inst->ReleaseInstructionBatch(batchCmd)) {
    std::cout << "Error: Could not release batchCmdh" << std::endl;
  }
  // Stop time sync master service
  timeSyncMaster->Stop();
  std::cout << "Application " << argv[0] << " exited" << std::endl;
  return 0;
}
