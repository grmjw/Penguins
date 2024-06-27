# Smart Access Baseline Changelog

## Release 5.2.1

- Add missing python bindings for linux gcc 12.

## Release 5.2.0

- Add platform support linux gcc 12 on x86_64, armv7hf and armv8.

## Release 5.1.2

- Fix dependency version conflict

## Release 5.1.1

- Improve Osal Documentation
- Improve Time Sync Master performance

## Release 5.1.0

- Support umrra4_automotive and umrr9f_t169_mse products

## Release 5.0.10

- Fix segfault when closing smart access and a static route is defined, but the sensor is not connected.

## Release 5.0.9

- Fix some compiler warnings
- Merge OSAL documentation into user manual

## Release 5.0.8

- Support msvc toolchain v141

## Release 5.0.7

- Fix segfault when closing device monitor
- On windows, logs are no longer output via the console. The logs are only
written to the log file.
- Documentation improvements

## Release 5.0.6

- Fix segfault when exiting the main loop

## Release 5.0.5

- Fix an incorrect comparison of instruction min values
- Fix segfault when sending instructions

## Release 5.0.4

- Fix python binding deadlock

## Release 5.0.3

- Fix the device monitor callback not being called after a sensor reset.

## Release 5.0.2

- Fix memory leaks

## Release 5.0.1

- Fix failure to decode can based data streams.
  Error Message: "Failed to set GPH size"

## Release 5.0.0

### Breaking

#### Datastream callback with two arguments

Old:

```c++
void ReceiveTargetListPortClbk(
    std::shared_ptr<com::master::tm_v6_2_3::targetlistport::TargetListPort> targetListPort)
{
  // Do stuff
}
auto comDataStreamServ = com::master::tm_v6_2_3::DataStreamServiceIface::Get();
    ReceiveTargetListPortCallback callback = 
                           std::bind(&ReceiveTargetListPortClbk,
                           std::placeholders::_1);
    if(ERROR_CODE_OK != comDataStreamServ->RegisterTargetListPortReceiveCallback(sensorClientId, callback))
    {
        std::cout << "Failed to register TargetListPort port callback" << std::endl;
    }

```

New:

```c++
void ReceiveTargetListPortClbk(
    std::shared_ptr<com::master::tm_v6_2_3::targetlistport::TargetListPort> targetListPort,
    com::types::ClientId clientId)
{
  // Do stuff
}

auto comDataStreamServ = com::master::tm_v6_2_3::DataStreamServiceIface::Get();
    ReceiveTargetListPortCallback callback = 
                           std::bind(&ReceiveTargetListPortClbk,
                           std::placeholders::_1,
                           std::placeholders::_2);
    if(ERROR_CODE_OK != comDataStreamServ->RegisterTargetListPortReceiveCallback(sensorClientId, callback))
    {
        std::cout << "Failed to register TargetListPort port callback" << std::endl;
    }
```

### Bugfixes

- Fix memory leak during receiving data
- Fix segfault when exiting the main loop

## Release 4.4.2

- Fix that the time sync master service sends many messages in a short period of time.
- Fix missing include in InstructionBatch.h.

## Release 4.4.1

- Fix that data from two clients with the same user interface but different serilization was not decoded.
- Performance update of update service.

## Release 4.4.0

- Fix loss of client when sensor restarted.
- Fix function GetResponse of ResponseBatch returning with no error code if there are no responses.
An empty vector was returned instead of an error code.
- With the new function GetNumberOfInstructions it is possible to check how many instructions the batch contains.
- An instruction batch without instructions can no longer be sent. An error code is returned when calling SendInstructionBatch.
- The example app can be built for armv7hf and armv8 architectures.

## Release 4.3.0

- Add platform support linux gcc 6 and gcc 9.
- Provide user interace files.
- Enable Time Sync Master Service.

## Release 4.2.0

- Add platform support linux armv7hf gcc 7.3 musl.
- Provide example osal sources.

## Release 4.1.1

- Fix incorrectly converted float values from instructions responses.

## Release 4.1.0

- Support const value for can based datastream.

## Release 4.0.1

- Fix segmentation fault when closing smart access

## Release 4.0.0

### Support Multi User Interfaces

- Each user interface has its own header files and lib (lib\<name>v\<version>_user_interface.so)
- Data Services are moved inside individual namespaces
- SmartAccess can identify the UserInterface of the sensor on its own. For static routes the UserInterfaces are added to the routing table.

### Instruction Service

- Add check number of instructions in one batch
  - Serilization type: can_based -> Max 10 instructions
  - Serilization type: port_based -> Max 255 instructions

- Change API from AllocateInstructionBatch and SendInstructionBatch
  - std::shared_ptr\<InstructionBatch\> AllocateInstructionBatch()
    to
    bool AllocateInstructionBatch(IN ClientId clientId,
                                  OUT std::shared_ptr\<InstructionBatch\> & batch)
  - ErrorCode SetInstructionBatch(IN std::set\<ClientId\>,
                                  IN std::shared_ptr\<InstructionBatch\>,
                                  IN ResponseCallback)
    to
    ErrorCode SendInstructionBatch(
      IN std::shared_ptr\<InstructionBatch\>,
      IN ResponseCallback)

### Update Service

- Performance improvements during SW update on CAN Based serialization

### Config Files

- Add format version check. Start with format version 1.0.0.
- Client ID value as hex or int
  
### Supports the following architectures

- linux-armv7hf
- linux-armv8
- linux-x86_64
- linux-x86
- windows-x86_64

### OSAL

- Change Namespace from com:common:osal to osal

### Bugfixes

- Name clashes with 3rd party libs are removed
