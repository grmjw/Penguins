// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from ouster_sensor_msgs:srv/GetMetadata.idl
// generated code does not contain a copyright notice
#include "ouster_sensor_msgs/srv/detail/get_metadata__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "ouster_sensor_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "ouster_sensor_msgs/srv/detail/get_metadata__struct.h"
#include "ouster_sensor_msgs/srv/detail/get_metadata__functions.h"
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


// forward declare type support functions


using _GetMetadata_Request__ros_msg_type = ouster_sensor_msgs__srv__GetMetadata_Request;

static bool _GetMetadata_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetMetadata_Request__ros_msg_type * ros_message = static_cast<const _GetMetadata_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: structure_needs_at_least_one_member
  {
    cdr << ros_message->structure_needs_at_least_one_member;
  }

  return true;
}

static bool _GetMetadata_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetMetadata_Request__ros_msg_type * ros_message = static_cast<_GetMetadata_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: structure_needs_at_least_one_member
  {
    cdr >> ros_message->structure_needs_at_least_one_member;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ouster_sensor_msgs
size_t get_serialized_size_ouster_sensor_msgs__srv__GetMetadata_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetMetadata_Request__ros_msg_type * ros_message = static_cast<const _GetMetadata_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name structure_needs_at_least_one_member
  {
    size_t item_size = sizeof(ros_message->structure_needs_at_least_one_member);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _GetMetadata_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_ouster_sensor_msgs__srv__GetMetadata_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ouster_sensor_msgs
size_t max_serialized_size_ouster_sensor_msgs__srv__GetMetadata_Request(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: structure_needs_at_least_one_member
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _GetMetadata_Request__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ouster_sensor_msgs__srv__GetMetadata_Request(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_GetMetadata_Request = {
  "ouster_sensor_msgs::srv",
  "GetMetadata_Request",
  _GetMetadata_Request__cdr_serialize,
  _GetMetadata_Request__cdr_deserialize,
  _GetMetadata_Request__get_serialized_size,
  _GetMetadata_Request__max_serialized_size
};

static rosidl_message_type_support_t _GetMetadata_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetMetadata_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, srv, GetMetadata_Request)() {
  return &_GetMetadata_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "ouster_sensor_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "ouster_sensor_msgs/srv/detail/get_metadata__struct.h"
// already included above
// #include "ouster_sensor_msgs/srv/detail/get_metadata__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

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

#include "rosidl_runtime_c/string.h"  // metadata
#include "rosidl_runtime_c/string_functions.h"  // metadata

// forward declare type support functions


using _GetMetadata_Response__ros_msg_type = ouster_sensor_msgs__srv__GetMetadata_Response;

static bool _GetMetadata_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetMetadata_Response__ros_msg_type * ros_message = static_cast<const _GetMetadata_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: metadata
  {
    const rosidl_runtime_c__String * str = &ros_message->metadata;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _GetMetadata_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetMetadata_Response__ros_msg_type * ros_message = static_cast<_GetMetadata_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: metadata
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->metadata.data) {
      rosidl_runtime_c__String__init(&ros_message->metadata);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->metadata,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'metadata'\n");
      return false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ouster_sensor_msgs
size_t get_serialized_size_ouster_sensor_msgs__srv__GetMetadata_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetMetadata_Response__ros_msg_type * ros_message = static_cast<const _GetMetadata_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name metadata
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->metadata.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _GetMetadata_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_ouster_sensor_msgs__srv__GetMetadata_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ouster_sensor_msgs
size_t max_serialized_size_ouster_sensor_msgs__srv__GetMetadata_Response(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: metadata
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  return current_alignment - initial_alignment;
}

static size_t _GetMetadata_Response__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ouster_sensor_msgs__srv__GetMetadata_Response(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_GetMetadata_Response = {
  "ouster_sensor_msgs::srv",
  "GetMetadata_Response",
  _GetMetadata_Response__cdr_serialize,
  _GetMetadata_Response__cdr_deserialize,
  _GetMetadata_Response__get_serialized_size,
  _GetMetadata_Response__max_serialized_size
};

static rosidl_message_type_support_t _GetMetadata_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetMetadata_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, srv, GetMetadata_Response)() {
  return &_GetMetadata_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "ouster_sensor_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "ouster_sensor_msgs/srv/get_metadata.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t GetMetadata__callbacks = {
  "ouster_sensor_msgs::srv",
  "GetMetadata",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, srv, GetMetadata_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, srv, GetMetadata_Response)(),
};

static rosidl_service_type_support_t GetMetadata__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &GetMetadata__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, srv, GetMetadata)() {
  return &GetMetadata__handle;
}

#if defined(__cplusplus)
}
#endif
