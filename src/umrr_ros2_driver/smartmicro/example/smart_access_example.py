"""Smart Acces Python Binding Example APP"""
from datetime import datetime
from time import sleep
import sys
import smart_access_binding as smart_access


def device_monitor_callback(client_id : int, client_connected : bool):
    print("Device Monitor Service: ClientId: {} is connected [{}]"
          .format(client_id, client_connected))

def instruction_callback(client_id: int, response_batch):
    print("Received Instruction Response from Client {}" .format(client_id))
    my_status_resp = smart_access.ResponseVector_u32()
    if response_batch.GetResponse_u32("software_info",
                                      "user_interface_v_major",
                                      my_status_resp):
        for response in my_status_resp:
            value = response.GetConvertValue()
            print("user_interface_v_major: {}" .format(value))
    else:
        print("No software_info response")

def time_base():
    timestamp = datetime.utcnow() - datetime(1900, 1, 1)
    seconds = int(timestamp.total_seconds())
    fractions_of_seconds = timestamp.microseconds
    ntp_timestamp = (seconds << 32) + fractions_of_seconds
    return ntp_timestamp

def init_smart_access(client_id : int):
    com_services = smart_access.CommunicationServicesIface.Get()
    if com_services.Init() is not True:
        raise Exception("Smart Access init failed")
    device_monitor_service = com_services.GetDeviceMonitorService()
    device_monitor_service.RegisterConnectedClientCallback(
        device_monitor_callback)
    sleep(5)
    client_connected = device_monitor_service.IsClientConnected(client_id)
    if client_connected:
        send_instruction(com_services, client_id)
    else:
        raise Exception(f"The client {client_id} is not connected")
    start_time_sync_master_service(com_services)

def send_instruction(com_services, client_id : int):
    instruction_service = com_services.GetInstructionService()

    batch = instruction_service.AllocateInstructionBatch(client_id)
    status_request = smart_access.GetStatusRequest_u32(
        "software_info", "user_interface_v_major")
    # param_request = smart_acess.GetParamRequest_f32("some_section",
    #                                                 "some_instruction")
    # param_set_request = smart_acess.SetParamRequest_i8("some_section",
    #                                                    "some_instruction")
    batch.AddRequest(status_request)
    status = instruction_service.SendInstructionBatch(batch,
                                                      instruction_callback)
    if smart_access.ErrorCode.ERROR_CODE_OK != status:
        raise Exception(f"Failed to sent the instruction batch {status}")
    sleep(5)

def start_time_sync_master_service(com_services):
    time_sync_service = com_services.GetTimeSyncServiceIface()
    if time_sync_service is None:
        raise Exception("Get time sync service failed")
    time_sync_master_service = time_sync_service.GetMasterService()
    if time_sync_master_service is None:
        raise Exception("Get time sync master service failed")
    # TODO Need to adjust slave sync id. This slave sync id must match sync id of the sensor
    slave_sync_id = 0
    if (smart_access.ErrorCode.ERROR_CODE_OK != 
        time_sync_master_service.AddSlave(slave_sync_id)):
        raise Exception(f"Failed to add {slave_sync_id}")
    if (smart_access.ErrorCode.ERROR_CODE_OK !=
        time_sync_master_service.RegisterRefTimeCallback(time_base)):
        raise Exception("Failed to register reference time callback")
    if (smart_access.ErrorCode.ERROR_CODE_OK !=
            time_sync_master_service.Start()):
        raise Exception("Failed to start time sync master service")

if __name__ == "__main__":
    print(sys.argv)
    if len(sys.argv) < 2:
        print("python smart_access_example.py <Client_Id>")
        raise Exception("Missing 1 required argument 'client id'")
    init_smart_access(client_id=int(sys.argv[1]))
