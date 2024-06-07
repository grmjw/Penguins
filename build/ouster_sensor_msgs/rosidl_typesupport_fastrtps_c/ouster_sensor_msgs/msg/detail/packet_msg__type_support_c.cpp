// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from ouster_sensor_msgs:msg/PacketMsg.idl
// generated code does not contain a copyright notice
#include "ouster_sensor_msgs/msg/detail/packet_msg__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "ouster_sensor_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "ouster_sensor_msgs/msg/detail/packet_msg__struct.h"
#include "ouster_sensor_msgs/msg/detail/packet_msg__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/primitives_sequence.h"  // buf
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // buf

// forward declare type support functions


using _PacketMsg__ros_msg_type = ouster_sensor_msgs__msg__PacketMsg;

static bool _PacketMsg__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _PacketMsg__ros_msg_type * ros_message = static_cast<const _PacketMsg__ros_msg_type *>(untyped_ros_message);
  // Field name: buf
  {
    size_t size = ros_message->buf.size;
    auto array_ptr = ros_message->buf.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _PacketMsg__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _PacketMsg__ros_msg_type * ros_message = static_cast<_PacketMsg__ros_msg_type *>(untyped_ros_message);
  // Field name: buf
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->buf.data) {
      rosidl_runtime_c__uint8__Sequence__fini(&ros_message->buf);
    }
    if (!rosidl_runtime_c__uint8__Sequence__init(&ros_message->buf, size)) {
      return "failed to create array for field 'buf'";
    }
    auto array_ptr = ros_message->buf.data;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ouster_sensor_msgs
size_t get_serialized_size_ouster_sensor_msgs__msg__PacketMsg(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _PacketMsg__ros_msg_type * ros_message = static_cast<const _PacketMsg__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name buf
  {
    size_t array_size = ros_message->buf.size;
    auto array_ptr = ros_message->buf.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _PacketMsg__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_ouster_sensor_msgs__msg__PacketMsg(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ouster_sensor_msgs
size_t max_serialized_size_ouster_sensor_msgs__msg__PacketMsg(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: buf
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _PacketMsg__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ouster_sensor_msgs__msg__PacketMsg(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_PacketMsg = {
  "ouster_sensor_msgs::msg",
  "PacketMsg",
  _PacketMsg__cdr_serialize,
  _PacketMsg__cdr_deserialize,
  _PacketMsg__get_serialized_size,
  _PacketMsg__max_serialized_size
};

static rosidl_message_type_support_t _PacketMsg__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_PacketMsg,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, msg, PacketMsg)() {
  return &_PacketMsg__type_support;
}

#if defined(__cplusplus)
}
#endif
