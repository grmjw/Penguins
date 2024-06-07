// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from slam_toolbox:srv/AddSubmap.idl
// generated code does not contain a copyright notice

#ifndef SLAM_TOOLBOX__SRV__DETAIL__ADD_SUBMAP__FUNCTIONS_H_
#define SLAM_TOOLBOX__SRV__DETAIL__ADD_SUBMAP__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "slam_toolbox/msg/rosidl_generator_c__visibility_control.h"

#include "slam_toolbox/srv/detail/add_submap__struct.h"

/// Initialize srv/AddSubmap message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * slam_toolbox__srv__AddSubmap_Request
 * )) before or use
 * slam_toolbox__srv__AddSubmap_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__AddSubmap_Request__init(slam_toolbox__srv__AddSubmap_Request * msg);

/// Finalize srv/AddSubmap message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__AddSubmap_Request__fini(slam_toolbox__srv__AddSubmap_Request * msg);

/// Create srv/AddSubmap message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * slam_toolbox__srv__AddSubmap_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
slam_toolbox__srv__AddSubmap_Request *
slam_toolbox__srv__AddSubmap_Request__create();

/// Destroy srv/AddSubmap message.
/**
 * It calls
 * slam_toolbox__srv__AddSubmap_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__AddSubmap_Request__destroy(slam_toolbox__srv__AddSubmap_Request * msg);

/// Check for srv/AddSubmap message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__AddSubmap_Request__are_equal(const slam_toolbox__srv__AddSubmap_Request * lhs, const slam_toolbox__srv__AddSubmap_Request * rhs);

/// Copy a srv/AddSubmap message.
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
slam_toolbox__srv__AddSubmap_Request__copy(
  const slam_toolbox__srv__AddSubmap_Request * input,
  slam_toolbox__srv__AddSubmap_Request * output);

/// Initialize array of srv/AddSubmap messages.
/**
 * It allocates the memory for the number of elements and calls
 * slam_toolbox__srv__AddSubmap_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__AddSubmap_Request__Sequence__init(slam_toolbox__srv__AddSubmap_Request__Sequence * array, size_t size);

/// Finalize array of srv/AddSubmap messages.
/**
 * It calls
 * slam_toolbox__srv__AddSubmap_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__AddSubmap_Request__Sequence__fini(slam_toolbox__srv__AddSubmap_Request__Sequence * array);

/// Create array of srv/AddSubmap messages.
/**
 * It allocates the memory for the array and calls
 * slam_toolbox__srv__AddSubmap_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
slam_toolbox__srv__AddSubmap_Request__Sequence *
slam_toolbox__srv__AddSubmap_Request__Sequence__create(size_t size);

/// Destroy array of srv/AddSubmap messages.
/**
 * It calls
 * slam_toolbox__srv__AddSubmap_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__AddSubmap_Request__Sequence__destroy(slam_toolbox__srv__AddSubmap_Request__Sequence * array);

/// Check for srv/AddSubmap message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__AddSubmap_Request__Sequence__are_equal(const slam_toolbox__srv__AddSubmap_Request__Sequence * lhs, const slam_toolbox__srv__AddSubmap_Request__Sequence * rhs);

/// Copy an array of srv/AddSubmap messages.
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
slam_toolbox__srv__AddSubmap_Request__Sequence__copy(
  const slam_toolbox__srv__AddSubmap_Request__Sequence * input,
  slam_toolbox__srv__AddSubmap_Request__Sequence * output);

/// Initialize srv/AddSubmap message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * slam_toolbox__srv__AddSubmap_Response
 * )) before or use
 * slam_toolbox__srv__AddSubmap_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__AddSubmap_Response__init(slam_toolbox__srv__AddSubmap_Response * msg);

/// Finalize srv/AddSubmap message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__AddSubmap_Response__fini(slam_toolbox__srv__AddSubmap_Response * msg);

/// Create srv/AddSubmap message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * slam_toolbox__srv__AddSubmap_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
slam_toolbox__srv__AddSubmap_Response *
slam_toolbox__srv__AddSubmap_Response__create();

/// Destroy srv/AddSubmap message.
/**
 * It calls
 * slam_toolbox__srv__AddSubmap_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__AddSubmap_Response__destroy(slam_toolbox__srv__AddSubmap_Response * msg);

/// Check for srv/AddSubmap message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__AddSubmap_Response__are_equal(const slam_toolbox__srv__AddSubmap_Response * lhs, const slam_toolbox__srv__AddSubmap_Response * rhs);

/// Copy a srv/AddSubmap message.
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
slam_toolbox__srv__AddSubmap_Response__copy(
  const slam_toolbox__srv__AddSubmap_Response * input,
  slam_toolbox__srv__AddSubmap_Response * output);

/// Initialize array of srv/AddSubmap messages.
/**
 * It allocates the memory for the number of elements and calls
 * slam_toolbox__srv__AddSubmap_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__AddSubmap_Response__Sequence__init(slam_toolbox__srv__AddSubmap_Response__Sequence * array, size_t size);

/// Finalize array of srv/AddSubmap messages.
/**
 * It calls
 * slam_toolbox__srv__AddSubmap_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__AddSubmap_Response__Sequence__fini(slam_toolbox__srv__AddSubmap_Response__Sequence * array);

/// Create array of srv/AddSubmap messages.
/**
 * It allocates the memory for the array and calls
 * slam_toolbox__srv__AddSubmap_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
slam_toolbox__srv__AddSubmap_Response__Sequence *
slam_toolbox__srv__AddSubmap_Response__Sequence__create(size_t size);

/// Destroy array of srv/AddSubmap messages.
/**
 * It calls
 * slam_toolbox__srv__AddSubmap_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
void
slam_toolbox__srv__AddSubmap_Response__Sequence__destroy(slam_toolbox__srv__AddSubmap_Response__Sequence * array);

/// Check for srv/AddSubmap message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_slam_toolbox
bool
slam_toolbox__srv__AddSubmap_Response__Sequence__are_equal(const slam_toolbox__srv__AddSubmap_Response__Sequence * lhs, const slam_toolbox__srv__AddSubmap_Response__Sequence * rhs);

/// Copy an array of srv/AddSubmap messages.
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
slam_toolbox__srv__AddSubmap_Response__Sequence__copy(
  const slam_toolbox__srv__AddSubmap_Response__Sequence * input,
  slam_toolbox__srv__AddSubmap_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SLAM_TOOLBOX__SRV__DETAIL__ADD_SUBMAP__FUNCTIONS_H_
