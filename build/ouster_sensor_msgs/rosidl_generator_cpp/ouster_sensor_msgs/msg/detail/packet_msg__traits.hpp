// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ouster_sensor_msgs:msg/PacketMsg.idl
// generated code does not contain a copyright notice

#ifndef OUSTER_SENSOR_MSGS__MSG__DETAIL__PACKET_MSG__TRAITS_HPP_
#define OUSTER_SENSOR_MSGS__MSG__DETAIL__PACKET_MSG__TRAITS_HPP_

#include "ouster_sensor_msgs/msg/detail/packet_msg__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ouster_sensor_msgs::msg::PacketMsg>()
{
  return "ouster_sensor_msgs::msg::PacketMsg";
}

template<>
inline const char * name<ouster_sensor_msgs::msg::PacketMsg>()
{
  return "ouster_sensor_msgs/msg/PacketMsg";
}

template<>
struct has_fixed_size<ouster_sensor_msgs::msg::PacketMsg>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ouster_sensor_msgs::msg::PacketMsg>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ouster_sensor_msgs::msg::PacketMsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OUSTER_SENSOR_MSGS__MSG__DETAIL__PACKET_MSG__TRAITS_HPP_
