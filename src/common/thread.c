#include "thread.h"

#include <assert.h>
#include <errno.h>

#ifdef HAVE_PTHREAD

nw_status nw_mutex_create(nw_mutex *mutex){
  assert(mutex != NULL);
  if(pthread_mutex_init(mutex, NULL)){
    switch(errno){
    case EAGAIN:
    case ENOMEM:
      return NW_MUTEX_RESOURCE_ERROR;
    case EPERM:
      return NW_PERMISSION_DENIED;
    case EBUSY:
      return NW_ALREADY_INITIALIZED;
    case EINVAL:
      return NW_INVALID_ARGUMENT;
    }
  }
  return NW_OK;
}

nw_status nw_mutex_lock(nw_mutex *mutex){
  assert(mutex != NULL);
  if(pthread_mutex_lock(mutex)){
    switch(errno){
    case EINVAL:
      return NW_NOT_INITIALIZED;
    case EAGAIN:
      return NW_MUTEX_RECURSIVE_LOCK_ERROR;
    case EDEADLK:
      return NW_MUTEX_ALREADY_OWNED;
    }
  }
  return NW_OK;
}

nw_status nw_mutex_unlock(nw_mutex *mutex){
  assert(mutex != NULL);
  if(pthread_mutex_unlock(mutex)){
    switch(errno){
    case EINVAL:
      return NW_NOT_INITIALIZED;
    case EAGAIN:
      return NW_MUTEX_RECURSIVE_LOCK_ERROR;
    case EPERM:
      return NW_MUTEX_NOT_OWNED;
    }
  }
  return NW_OK;
}

nw_status nw_mutex_destroy(nw_mutex *mutex){
  assert(mutex != NULL);
  if(pthread_mutex_destroy(mutex)){
    switch(errno){
    case EBUSY:
      return NW_MUTEX_ALREADY_LOCKED;
    case EINVAL:
      return NW_NOT_INITIALIZED;
    }
  }
  return NW_OK;
}
  
#endif
