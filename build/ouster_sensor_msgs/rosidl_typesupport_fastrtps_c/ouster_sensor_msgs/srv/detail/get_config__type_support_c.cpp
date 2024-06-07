// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from ouster_sensor_msgs:srv/GetConfig.idl
// generated code does not contain a copyright notice
#include "ouster_sensor_msgs/srv/detail/get_config__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "ouster_sensor_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "ouster_sensor_msgs/srv/detail/get_config__struct.h"
#include "ouster_sensor_msgs/srv/detail/get_config__functions.h"
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


using _GetConfig_Request__ros_msg_type = ouster_sensor_msgs__srv__GetConfig_Request;

static bool _GetConfig_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetConfig_Request__ros_msg_type * ros_message = static_cast<const _GetConfig_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: structure_needs_at_least_one_member
  {
    cdr << ros_message->structure_needs_at_least_one_member;
  }

  return true;
}

static bool _GetConfig_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetConfig_Request__ros_msg_type * ros_message = static_cast<_GetConfig_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: structure_needs_at_least_one_member
  {
    cdr >> ros_message->structure_needs_at_least_one_member;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ouster_sensor_msgs
size_t get_serialized_size_ouster_sensor_msgs__srv__GetConfig_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetConfig_Request__ros_msg_type * ros_message = static_cast<const _GetConfig_Request__ros_msg_type *>(untyped_ros_message);
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

static uint32_t _GetConfig_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_ouster_sensor_msgs__srv__GetConfig_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ouster_sensor_msgs
size_t max_serialized_size_ouster_sensor_msgs__srv__GetConfig_Request(
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

static size_t _GetConfig_Request__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ouster_sensor_msgs__srv__GetConfig_Request(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_GetConfig_Request = {
  "ouster_sensor_msgs::srv",
  "GetConfig_Request",
  _GetConfig_Request__cdr_serialize,
  _GetConfig_Request__cdr_deserialize,
  _GetConfig_Request__get_serialized_size,
  _GetConfig_Request__max_serialized_size
};

static rosidl_message_type_support_t _GetConfig_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetConfig_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, srv, GetConfig_Request)() {
  return &_GetConfig_Request__type_support;
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
// #include "ouster_sensor_msgs/srv/detail/get_config__struct.h"
// already included above
// #include "ouster_sensor_msgs/srv/detail/get_config__functions.h"
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

#include "rosidl_runtime_c/string.h"  // config
#include "rosidl_runtime_c/string_functions.h"  // config

// forward declare type support functions


using _GetConfig_Response__ros_msg_type = ouster_sensor_msgs__srv__GetConfig_Response;

static bool _GetConfig_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetConfig_Response__ros_msg_type * ros_message = static_cast<const _GetConfig_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: config
  {
    const rosidl_runtime_c__String * str = &ros_message->config;
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

static bool _GetConfig_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetConfig_Response__ros_msg_type * ros_message = static_cast<_GetConfig_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: config
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->config.data) {
      rosidl_runtime_c__String__init(&ros_message->config);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->config,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'config'\n");
      return false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ouster_sensor_msgs
size_t get_serialized_size_ouster_sensor_msgs__srv__GetConfig_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetConfig_Response__ros_msg_type * ros_message = static_cast<const _GetConfig_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name config
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->config.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _GetConfig_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_ouster_sensor_msgs__srv__GetConfig_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ouster_sensor_msgs
size_t max_serialized_size_ouster_sensor_msgs__srv__GetConfig_Response(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: config
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

static size_t _GetConfig_Response__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ouster_sensor_msgs__srv__GetConfig_Response(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_GetConfig_Response = {
  "ouster_sensor_msgs::srv",
  "GetConfig_Response",
  _GetConfig_Response__cdr_serialize,
  _GetConfig_Response__cdr_deserialize,
  _GetConfig_Response__get_serialized_size,
  _GetConfig_Response__max_serialized_size
};

static rosidl_message_type_support_t _GetConfig_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetConfig_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, srv, GetConfig_Response)() {
  return &_GetConfig_Response__type_support;
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
#include "ouster_sensor_msgs/srv/get_config.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t GetConfig__callbacks = {
  "ouster_sensor_msgs::srv",
  "GetConfig",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, srv, GetConfig_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, srv, GetConfig_Response)(),
};

static rosidl_service_type_support_t GetConfig__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &GetConfig__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ouster_sensor_msgs, srv, GetConfig)() {
  return &GetConfig__handle;
}

#if defined(__cplusplus)
}
#endif
