// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from slam_toolbox:srv/MergeMaps.idl
// generated code does not contain a copyright notice
#include "slam_toolbox/srv/detail/merge_maps__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
slam_toolbox__srv__MergeMaps_Request__init(slam_toolbox__srv__MergeMaps_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
slam_toolbox__srv__MergeMaps_Request__fini(slam_toolbox__srv__MergeMaps_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
slam_toolbox__srv__MergeMaps_Request__are_equal(const slam_toolbox__srv__MergeMaps_Request * lhs, const slam_toolbox__srv__MergeMaps_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
slam_toolbox__srv__MergeMaps_Request__copy(
  const slam_toolbox__srv__MergeMaps_Request * input,
  slam_toolbox__srv__MergeMaps_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

slam_toolbox__srv__MergeMaps_Request *
slam_toolbox__srv__MergeMaps_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  slam_toolbox__srv__MergeMaps_Request * msg = (slam_toolbox__srv__MergeMaps_Request *)allocator.allocate(sizeof(slam_toolbox__srv__MergeMaps_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(slam_toolbox__srv__MergeMaps_Request));
  bool success = slam_toolbox__srv__MergeMaps_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
slam_toolbox__srv__MergeMaps_Request__destroy(slam_toolbox__srv__MergeMaps_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    slam_toolbox__srv__MergeMaps_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
slam_toolbox__srv__MergeMaps_Request__Sequence__init(slam_toolbox__srv__MergeMaps_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  slam_toolbox__srv__MergeMaps_Request * data = NULL;

  if (size) {
    data = (slam_toolbox__srv__MergeMaps_Request *)allocator.zero_allocate(size, sizeof(slam_toolbox__srv__MergeMaps_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = slam_toolbox__srv__MergeMaps_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        slam_toolbox__srv__MergeMaps_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
slam_toolbox__srv__MergeMaps_Request__Sequence__fini(slam_toolbox__srv__MergeMaps_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      slam_toolbox__srv__MergeMaps_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

slam_toolbox__srv__MergeMaps_Request__Sequence *
slam_toolbox__srv__MergeMaps_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  slam_toolbox__srv__MergeMaps_Request__Sequence * array = (slam_toolbox__srv__MergeMaps_Request__Sequence *)allocator.allocate(sizeof(slam_toolbox__srv__MergeMaps_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = slam_toolbox__srv__MergeMaps_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
slam_toolbox__srv__MergeMaps_Request__Sequence__destroy(slam_toolbox__srv__MergeMaps_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    slam_toolbox__srv__MergeMaps_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
slam_toolbox__srv__MergeMaps_Request__Sequence__are_equal(const slam_toolbox__srv__MergeMaps_Request__Sequence * lhs, const slam_toolbox__srv__MergeMaps_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!slam_toolbox__srv__MergeMaps_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
slam_toolbox__srv__MergeMaps_Request__Sequence__copy(
  const slam_toolbox__srv__MergeMaps_Request__Sequence * input,
  slam_toolbox__srv__MergeMaps_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(slam_toolbox__srv__MergeMaps_Request);
    slam_toolbox__srv__MergeMaps_Request * data =
      (slam_toolbox__srv__MergeMaps_Request *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!slam_toolbox__srv__MergeMaps_Request__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          slam_toolbox__srv__MergeMaps_Request__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!slam_toolbox__srv__MergeMaps_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
slam_toolbox__srv__MergeMaps_Response__init(slam_toolbox__srv__MergeMaps_Response * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
slam_toolbox__srv__MergeMaps_Response__fini(slam_toolbox__srv__MergeMaps_Response * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
slam_toolbox__srv__MergeMaps_Response__are_equal(const slam_toolbox__srv__MergeMaps_Response * lhs, const slam_toolbox__srv__MergeMaps_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
slam_toolbox__srv__MergeMaps_Response__copy(
  const slam_toolbox__srv__MergeMaps_Response * input,
  slam_toolbox__srv__MergeMaps_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

slam_toolbox__srv__MergeMaps_Response *
slam_toolbox__srv__MergeMaps_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  slam_toolbox__srv__MergeMaps_Response * msg = (slam_toolbox__srv__MergeMaps_Response *)allocator.allocate(sizeof(slam_toolbox__srv__MergeMaps_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(slam_toolbox__srv__MergeMaps_Response));
  bool success = slam_toolbox__srv__MergeMaps_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
slam_toolbox__srv__MergeMaps_Response__destroy(slam_toolbox__srv__MergeMaps_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    slam_toolbox__srv__MergeMaps_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
slam_toolbox__srv__MergeMaps_Response__Sequence__init(slam_toolbox__srv__MergeMaps_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  slam_toolbox__srv__MergeMaps_Response * data = NULL;

  if (size) {
    data = (slam_toolbox__srv__MergeMaps_Response *)allocator.zero_allocate(size, sizeof(slam_toolbox__srv__MergeMaps_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = slam_toolbox__srv__MergeMaps_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        slam_toolbox__srv__MergeMaps_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
slam_toolbox__srv__MergeMaps_Response__Sequence__fini(slam_toolbox__srv__MergeMaps_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      slam_toolbox__srv__MergeMaps_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

slam_toolbox__srv__MergeMaps_Response__Sequence *
slam_toolbox__srv__MergeMaps_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  slam_toolbox__srv__MergeMaps_Response__Sequence * array = (slam_toolbox__srv__MergeMaps_Response__Sequence *)allocator.allocate(sizeof(slam_toolbox__srv__MergeMaps_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = slam_toolbox__srv__MergeMaps_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
slam_toolbox__srv__MergeMaps_Response__Sequence__destroy(slam_toolbox__srv__MergeMaps_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    slam_toolbox__srv__MergeMaps_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
slam_toolbox__srv__MergeMaps_Response__Sequence__are_equal(const slam_toolbox__srv__MergeMaps_Response__Sequence * lhs, const slam_toolbox__srv__MergeMaps_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!slam_toolbox__srv__MergeMaps_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
slam_toolbox__srv__MergeMaps_Response__Sequence__copy(
  const slam_toolbox__srv__MergeMaps_Response__Sequence * input,
  slam_toolbox__srv__MergeMaps_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(slam_toolbox__srv__MergeMaps_Response);
    slam_toolbox__srv__MergeMaps_Response * data =
      (slam_toolbox__srv__MergeMaps_Response *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!slam_toolbox__srv__MergeMaps_Response__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          slam_toolbox__srv__MergeMaps_Response__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!slam_toolbox__srv__MergeMaps_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
