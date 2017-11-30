#include "array.h"

#include <assert.h>
#include <stdlib.h>

static nw_status default_element_destroy(nw_element *value){
  return NW_OK;
}

const size_t nw_default_initial_size = 8;

const struct nw_array_policy nw_default_array_policy = {&default_element_destroy};

struct nw_array{
  nw_element *data;
  size_t length;
  size_t size;
  const struct nw_array_policy *policy;
};

nw_status nw_array_create(nw_array_ref *dest, size_t initial_size, const struct nw_array_policy *policy){
  assert(dest != NULL);
  nw_array_ref array = malloc(sizeof(struct nw_array));
  if(array == NULL){
    return NW_ALLOC_ERROR;
  }
  if(initial_size == 0){
    initial_size = nw_default_initial_size;
  }
  if(policy == NULL){
    policy = &nw_default_array_policy;
  }else{
    assert(policy->destroy != NULL);
  }
  array->data = malloc(sizeof(nw_element) * initial_size);
  if(array->data == NULL){
    free(array);
    return NW_ALLOC_ERROR;
  }
  array->size = initial_size;
  array->policy = policy;
  return NW_OK;
}

nw_status nw_array_ensure(nw_array_ref array, size_t min_capacity){
  assert(array != NULL);
  if(array->size < min_capacity){
    size_t new_size = array->size;
    do{
      new_size <<= 1;
    }while(new_size < min_capacity);
    nw_element *buffer = realloc(array->data, sizeof(nw_element) * new_size);
    if(buffer == NULL){
      return NW_ALLOC_ERROR;
    }
    array->data = buffer;
    array->size = new_size;
  }
  return NW_OK;
}

nw_status nw_array_push_back(nw_array_ref array, nw_element value){
  assert(array != NULL);
  nw_status status = nw_array_ensure(array, array->length+1);
  if(status){
    return status;
  }
  array->data[array->length] = value;
  ++array->length;
  return NW_OK;
}

nw_status nw_array_pop_back(nw_array_ref array){
  assert(array != NULL);
  if(array->length == 0){
    return NW_EMPTY;
  }
  nw_status status = (*array->policy->destroy)(array->data + array->length);
  if(status){
    return status;
  }
  --array->length;
  return NW_OK;
}

size_t nw_array_length(nw_array_cref array){
  assert(array != NULL);
  return array->length;
}

nw_element nw_array_at(nw_array_cref array, size_t index){
  assert(array != NULL);
  return array->data[index];
}

nw_status nw_array_at_checked(nw_array_cref array, size_t index, nw_element *dest){
  assert(array != NULL);
  assert(dest != NULL);
  if(array->length <= index){
    return NW_OUT_OF_BOUNDS;
  }
  *dest = array->data[index];
  return NW_OK;
}

void nw_array_destroy(nw_array_ref *src){
  assert(src != NULL);
  nw_array_ref array = *src;
  assert(array != NULL);
  for(size_t i = 0; i < array->length; ++i){
    (*array->policy->destroy)(array->data + array->length);
  }
  free(array->data);
  free(array);
}
