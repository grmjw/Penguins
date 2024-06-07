// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ouster_sensor_msgs:msg/PacketMsg.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ouster_sensor_msgs/msg/detail/packet_msg__rosidl_typesupport_introspection_c.h"
#include "ouster_sensor_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ouster_sensor_msgs/msg/detail/packet_msg__functions.h"
#include "ouster_sensor_msgs/msg/detail/packet_msg__struct.h"


// Include directives for member types
// Member `buf`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ouster_sensor_msgs__msg__PacketMsg__init(message_memory);
}

void PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_fini_function(void * message_memory)
{
  ouster_sensor_msgs__msg__PacketMsg__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_message_member_array[1] = {
  {
    "buf",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ouster_sensor_msgs__msg__PacketMsg, buf),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_message_members = {
  "ouster_sensor_msgs__msg",  // message namespace
  "PacketMsg",  // message name
  1,  // number of fields
  sizeof(ouster_sensor_msgs__msg__PacketMsg),
  PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_message_member_array,  // message members
  PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_init_function,  // function to initialize message memory (memory has to be allocated)
  PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_message_type_support_handle = {
  0,
  &PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ouster_sensor_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ouster_sensor_msgs, msg, PacketMsg)() {
  if (!PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_message_type_support_handle.typesupport_identifier) {
    PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &PacketMsg__rosidl_typesupport_introspection_c__PacketMsg_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
