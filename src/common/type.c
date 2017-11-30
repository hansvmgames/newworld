#include "type.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

const char * nw_status_message(nw_status status){
  switch(status){
  case NW_OK:
    return "ok";
  case NW_ERROR:
    return "unspecified error";
  case NW_ALLOC_ERROR:
    return "memory allocation failed";
  case NW_ALREADY_INITIALIZED:
    return "already initialized";
  case NW_NOT_INITIALIZED:
    return "not initialized";
  case NW_INVALID_ARGUMENT:
    return "invalid argument";
  case NW_INVALID_STATE:
    return "invalid state";
  case NW_EMPTY:
    return "empty";
  case NW_OUT_OF_BOUNDS:
    return "out of bounds";
  case NW_IO_ERROR:
    return "input/output error";
  case NW_MUTEX_RESOURCE_ERROR:
    return "system lacks resources to initialize mutex";
  case NW_MUTEX_ALREADY_LOCKED:
    return "mutex already locked";
  case NW_MUTEX_RECURSIVE_LOCK_ERROR:
    return "mutex max recursive locks reached";
  case NW_MUTEX_ALREADY_OWNED:
    return "thread already owns mutex";
  case NW_MUTEX_NOT_OWNED:
    return "thread does not own mutex";
  case NW_PERMISSION_DENIED:
    return "permission denied";
  default:
    return "unknown error";
  }
}

nw_status nw_string_init(struct nw_string *string, size_t length){
  assert(string != NULL);
  if(length == 0){
    string->data = NULL;
  }else{
    string->data = malloc(sizeof(nw_char) * length);
    if(string->data == NULL){
      return NW_ALLOC_ERROR;
    }
  }
  string->length = length;
  return NW_OK;
}

void nw_string_init_empty(struct nw_string *string){
  assert(string != NULL);
  string->data = NULL;
  string->length = 0;
}

nw_status nw_string_resize(struct nw_string *string, size_t new_length){
  if(new_length != string->length){
    if(new_length == 0){
      free(string->data);
      string->data = NULL;
    }else{
      nw_char *buffer = realloc(string->data, sizeof(nw_char) * new_length);
      if(buffer == NULL){
	return NW_ALLOC_ERROR;
      }
      string->data = buffer;
    }
  }
  string->length = new_length;
  return NW_OK;
}

nw_status nw_string_concat(struct nw_string *dest, const struct nw_string *src){
  size_t orig_length = dest->length;
  nw_status status = nw_string_resize(dest, dest->length + src->length);
  if(status){
    return status;
  }
  memcpy(dest->data + orig_length * sizeof(nw_char), src->data, src->length * sizeof(nw_char));
  return NW_OK;
}

void nw_string_clear(struct nw_string *string){
  assert(string != NULL);
  free(string->data);
  string->data = NULL;
  string->length = 0;
}
