// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ouster_sensor_msgs:srv/GetConfig.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ouster_sensor_msgs/srv/detail/get_config__rosidl_typesupport_introspection_c.h"
#include "ouster_sensor_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ouster_sensor_msgs/srv/detail/get_config__functions.h"
#include "ouster_sensor_msgs/srv/detail/get_config__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ouster_sensor_msgs__srv__GetConfig_Request__init(message_memory);
}

void GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_fini_function(void * message_memory)
{
  ouster_sensor_msgs__srv__GetConfig_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ouster_sensor_msgs__srv__GetConfig_Request, structure_needs_at_least_one_member),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_message_members = {
  "ouster_sensor_msgs__srv",  // message namespace
  "GetConfig_Request",  // message name
  1,  // number of fields
  sizeof(ouster_sensor_msgs__srv__GetConfig_Request),
  GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_message_member_array,  // message members
  GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_message_type_support_handle = {
  0,
  &GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ouster_sensor_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ouster_sensor_msgs, srv, GetConfig_Request)() {
  if (!GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_message_type_support_handle.typesupport_identifier) {
    GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &GetConfig_Request__rosidl_typesupport_introspection_c__GetConfig_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "ouster_sensor_msgs/srv/detail/get_config__rosidl_typesupport_introspection_c.h"
// already included above
// #include "ouster_sensor_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "ouster_sensor_msgs/srv/detail/get_config__functions.h"
// already included above
// #include "ouster_sensor_msgs/srv/detail/get_config__struct.h"


// Include directives for member types
// Member `config`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ouster_sensor_msgs__srv__GetConfig_Response__init(message_memory);
}

void GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_fini_function(void * message_memory)
{
  ouster_sensor_msgs__srv__GetConfig_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_message_member_array[1] = {
  {
    "config",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ouster_sensor_msgs__srv__GetConfig_Response, config),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_message_members = {
  "ouster_sensor_msgs__srv",  // message namespace
  "GetConfig_Response",  // message name
  1,  // number of fields
  sizeof(ouster_sensor_msgs__srv__GetConfig_Response),
  GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_message_member_array,  // message members
  GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_message_type_support_handle = {
  0,
  &GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ouster_sensor_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ouster_sensor_msgs, srv, GetConfig_Response)() {
  if (!GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_message_type_support_handle.typesupport_identifier) {
    GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &GetConfig_Response__rosidl_typesupport_introspection_c__GetConfig_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "ouster_sensor_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "ouster_sensor_msgs/srv/detail/get_config__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers ouster_sensor_msgs__srv__detail__get_config__rosidl_typesupport_introspection_c__GetConfig_service_members = {
  "ouster_sensor_msgs__srv",  // service namespace
  "GetConfig",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // ouster_sensor_msgs__srv__detail__get_config__rosidl_typesupport_introspection_c__GetConfig_Request_message_type_support_handle,
  NULL  // response message
  // ouster_sensor_msgs__srv__detail__get_config__rosidl_typesupport_introspection_c__GetConfig_Response_message_type_support_handle
};

static rosidl_service_type_support_t ouster_sensor_msgs__srv__detail__get_config__rosidl_typesupport_introspection_c__GetConfig_service_type_support_handle = {
  0,
  &ouster_sensor_msgs__srv__detail__get_config__rosidl_typesupport_introspection_c__GetConfig_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ouster_sensor_msgs, srv, GetConfig_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ouster_sensor_msgs, srv, GetConfig_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ouster_sensor_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ouster_sensor_msgs, srv, GetConfig)() {
  if (!ouster_sensor_msgs__srv__detail__get_config__rosidl_typesupport_introspection_c__GetConfig_service_type_support_handle.typesupport_identifier) {
    ouster_sensor_msgs__srv__detail__get_config__rosidl_typesupport_introspection_c__GetConfig_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)ouster_sensor_msgs__srv__detail__get_config__rosidl_typesupport_introspection_c__GetConfig_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ouster_sensor_msgs, srv, GetConfig_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ouster_sensor_msgs, srv, GetConfig_Response)()->data;
  }

  return &ouster_sensor_msgs__srv__detail__get_config__rosidl_typesupport_introspection_c__GetConfig_service_type_support_handle;
}
