// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ouster_sensor_msgs:srv/GetMetadata.idl
// generated code does not contain a copyright notice

#ifndef OUSTER_SENSOR_MSGS__SRV__DETAIL__GET_METADATA__TRAITS_HPP_
#define OUSTER_SENSOR_MSGS__SRV__DETAIL__GET_METADATA__TRAITS_HPP_

#include "ouster_sensor_msgs/srv/detail/get_metadata__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ouster_sensor_msgs::srv::GetMetadata_Request>()
{
  return "ouster_sensor_msgs::srv::GetMetadata_Request";
}

template<>
inline const char * name<ouster_sensor_msgs::srv::GetMetadata_Request>()
{
  return "ouster_sensor_msgs/srv/GetMetadata_Request";
}

template<>
struct has_fixed_size<ouster_sensor_msgs::srv::GetMetadata_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<ouster_sensor_msgs::srv::GetMetadata_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<ouster_sensor_msgs::srv::GetMetadata_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ouster_sensor_msgs::srv::GetMetadata_Response>()
{
  return "ouster_sensor_msgs::srv::GetMetadata_Response";
}

template<>
inline const char * name<ouster_sensor_msgs::srv::GetMetadata_Response>()
{
  return "ouster_sensor_msgs/srv/GetMetadata_Response";
}

template<>
struct has_fixed_size<ouster_sensor_msgs::srv::GetMetadata_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ouster_sensor_msgs::srv::GetMetadata_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ouster_sensor_msgs::srv::GetMetadata_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ouster_sensor_msgs::srv::GetMetadata>()
{
  return "ouster_sensor_msgs::srv::GetMetadata";
}

template<>
inline const char * name<ouster_sensor_msgs::srv::GetMetadata>()
{
  return "ouster_sensor_msgs/srv/GetMetadata";
}

template<>
struct has_fixed_size<ouster_sensor_msgs::srv::GetMetadata>
  : std::integral_constant<
    bool,
    has_fixed_size<ouster_sensor_msgs::srv::GetMetadata_Request>::value &&
    has_fixed_size<ouster_sensor_msgs::srv::GetMetadata_Response>::value
  >
{
};

template<>
struct has_bounded_size<ouster_sensor_msgs::srv::GetMetadata>
  : std::integral_constant<
    bool,
    has_bounded_size<ouster_sensor_msgs::srv::GetMetadata_Request>::value &&
    has_bounded_size<ouster_sensor_msgs::srv::GetMetadata_Response>::value
  >
{
};

template<>
struct is_service<ouster_sensor_msgs::srv::GetMetadata>
  : std::true_type
{
};

template<>
struct is_service_request<ouster_sensor_msgs::srv::GetMetadata_Request>
  : std::true_type
{
};

template<>
struct is_service_response<ouster_sensor_msgs::srv::GetMetadata_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // OUSTER_SENSOR_MSGS__SRV__DETAIL__GET_METADATA__TRAITS_HPP_
