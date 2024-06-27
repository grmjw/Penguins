// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from slam_toolbox:srv/DeserializePoseGraph.idl
// generated code does not contain a copyright notice

#ifndef SLAM_TOOLBOX__SRV__DETAIL__DESERIALIZE_POSE_GRAPH__FUNCTIONS_H_
#define SLAM_TOOLBOX__SRV__DETAIL__DESERIALIZE_POSE_GRAPH__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "slam_toolbox/msg/rosidl_generator_c__visibility_control.h"

#include "slam_toolbox/srv/detail/deserialize_pose_graph__struct.h"

/// Initialize srv/DeserializePoseGraph message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * slam_toolbox__srv__DeserializePoseGraph_Request
 * )) before or use
 * slam_toolbox__srv__DeserializePoseGraph_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Request__init(slam_toolbox__srv__DeserializePoseGraph_Request * msg);

/// Finalize srv/DeserializePoseGraph message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__DeserializePoseGraph_Request__fini(slam_toolbox__srv__DeserializePoseGraph_Request * msg);

/// Create srv/DeserializePoseGraph message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * slam_toolbox__srv__DeserializePoseGraph_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
slam_toolbox__srv__DeserializePoseGraph_Request *
slam_toolbox__srv__DeserializePoseGraph_Request__create();

/// Destroy srv/DeserializePoseGraph message.
/**
 * It calls
 * slam_toolbox__srv__DeserializePoseGraph_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__DeserializePoseGraph_Request__destroy(slam_toolbox__srv__DeserializePoseGraph_Request * msg);

/// Check for srv/DeserializePoseGraph message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Request__are_equal(const slam_toolbox__srv__DeserializePoseGraph_Request * lhs, const slam_toolbox__srv__DeserializePoseGraph_Request * rhs);

/// Copy a srv/DeserializePoseGraph message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Request__copy(
  const slam_toolbox__srv__DeserializePoseGraph_Request * input,
  slam_toolbox__srv__DeserializePoseGraph_Request * output);

/// Initialize array of srv/DeserializePoseGraph messages.
/**
 * It allocates the memory for the number of elements and calls
 * slam_toolbox__srv__DeserializePoseGraph_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Request__Sequence__init(slam_toolbox__srv__DeserializePoseGraph_Request__Sequence * array, size_t size);

/// Finalize array of srv/DeserializePoseGraph messages.
/**
 * It calls
 * slam_toolbox__srv__DeserializePoseGraph_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__DeserializePoseGraph_Request__Sequence__fini(slam_toolbox__srv__DeserializePoseGraph_Request__Sequence * array);

/// Create array of srv/DeserializePoseGraph messages.
/**
 * It allocates the memory for the array and calls
 * slam_toolbox__srv__DeserializePoseGraph_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
slam_toolbox__srv__DeserializePoseGraph_Request__Sequence *
slam_toolbox__srv__DeserializePoseGraph_Request__Sequence__create(size_t size);

/// Destroy array of srv/DeserializePoseGraph messages.
/**
 * It calls
 * slam_toolbox__srv__DeserializePoseGraph_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__DeserializePoseGraph_Request__Sequence__destroy(slam_toolbox__srv__DeserializePoseGraph_Request__Sequence * array);

/// Check for srv/DeserializePoseGraph message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Request__Sequence__are_equal(const slam_toolbox__srv__DeserializePoseGraph_Request__Sequence * lhs, const slam_toolbox__srv__DeserializePoseGraph_Request__Sequence * rhs);

/// Copy an array of srv/DeserializePoseGraph messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Request__Sequence__copy(
  const slam_toolbox__srv__DeserializePoseGraph_Request__Sequence * input,
  slam_toolbox__srv__DeserializePoseGraph_Request__Sequence * output);

/// Initialize srv/DeserializePoseGraph message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * slam_toolbox__srv__DeserializePoseGraph_Response
 * )) before or use
 * slam_toolbox__srv__DeserializePoseGraph_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Response__init(slam_toolbox__srv__DeserializePoseGraph_Response * msg);

/// Finalize srv/DeserializePoseGraph message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__DeserializePoseGraph_Response__fini(slam_toolbox__srv__DeserializePoseGraph_Response * msg);

/// Create srv/DeserializePoseGraph message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * slam_toolbox__srv__DeserializePoseGraph_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
slam_toolbox__srv__DeserializePoseGraph_Response *
slam_toolbox__srv__DeserializePoseGraph_Response__create();

/// Destroy srv/DeserializePoseGraph message.
/**
 * It calls
 * slam_toolbox__srv__DeserializePoseGraph_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__DeserializePoseGraph_Response__destroy(slam_toolbox__srv__DeserializePoseGraph_Response * msg);

/// Check for srv/DeserializePoseGraph message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Response__are_equal(const slam_toolbox__srv__DeserializePoseGraph_Response * lhs, const slam_toolbox__srv__DeserializePoseGraph_Response * rhs);

/// Copy a srv/DeserializePoseGraph message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Response__copy(
  const slam_toolbox__srv__DeserializePoseGraph_Response * input,
  slam_toolbox__srv__DeserializePoseGraph_Response * output);

/// Initialize array of srv/DeserializePoseGraph messages.
/**
 * It allocates the memory for the number of elements and calls
 * slam_toolbox__srv__DeserializePoseGraph_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Response__Sequence__init(slam_toolbox__srv__DeserializePoseGraph_Response__Sequence * array, size_t size);

/// Finalize array of srv/DeserializePoseGraph messages.
/**
 * It calls
 * slam_toolbox__srv__DeserializePoseGraph_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__DeserializePoseGraph_Response__Sequence__fini(slam_toolbox__srv__DeserializePoseGraph_Response__Sequence * array);

/// Create array of srv/DeserializePoseGraph messages.
/**
 * It allocates the memory for the array and calls
 * slam_toolbox__srv__DeserializePoseGraph_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
slam_toolbox__srv__DeserializePoseGraph_Response__Sequence *
slam_toolbox__srv__DeserializePoseGraph_Response__Sequence__create(size_t size);

/// Destroy array of srv/DeserializePoseGraph messages.
/**
 * It calls
 * slam_toolbox__srv__DeserializePoseGraph_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__DeserializePoseGraph_Response__Sequence__destroy(slam_toolbox__srv__DeserializePoseGraph_Response__Sequence * array);

/// Check for srv/DeserializePoseGraph message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Response__Sequence__are_equal(const slam_toolbox__srv__DeserializePoseGraph_Response__Sequence * lhs, const slam_toolbox__srv__DeserializePoseGraph_Response__Sequence * rhs);

/// Copy an array of srv/DeserializePoseGraph messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__DeserializePoseGraph_Response__Sequence__copy(
  const slam_toolbox__srv__DeserializePoseGraph_Response__Sequence * input,
  slam_toolbox__srv__DeserializePoseGraph_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SLAM_TOOLBOX__SRV__DETAIL__DESERIALIZE_POSE_GRAPH__FUNCTIONS_H_
