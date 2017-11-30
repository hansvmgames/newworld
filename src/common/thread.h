#ifndef NW_COMMON_THREAD_H
#define NW_COMMON_THREAD_H

#include "config.h"
#include "type.h"

#ifdef HAVE_PTHREAD

#include <pthread.h>

#define NW_HAVE_THREAD

/**
 *an alias for the pthread mutex handle
 */
typedef pthread_mutex_t nw_mutex;

#endif

#ifdef NW_HAVE_THREAD

/**
 *creates a normal mutex
 *@param mutex the mutex to initialize
 *@return NW_OK on success
 *NW_MUTEX_RESOURCE_ERROR if the system lacks the resources to create the mutex
 *NW_PERMISSION_DENIED if the program does not have permission to create a mutex
 *NW_ALREADY_INITIALIZED if the mutex was already initialized
 *NW_INVALID_ARGUMENT if the parameters specifying the mutex were invalid
 */
nw_status nw_mutex_create(nw_mutex *mutex);

/**
 *locks a mutex, blocks the thread until the mutex is locked or an error occurs
 *@param mutex the mutex
 *@return NW_OK on success
 *NW_NOT_INITIALIZED if the mutex was not initialized
 *NW_RECURSIVE_LOCK_ERROR if the max number of recursive locks on this mutex was reached
 *NW_MUTEX_ALREADY_OWNED if this thread already owns the mutex
 */
nw_status nw_mutex_lock(nw_mutex *mutex);

/**
 *unlocks a mutex
 *@param mutex the mutex
 *@return NW_OK on success
 *NW_NOT_INITIALIZED if the mutex was not initialized
 *NW_RECURSIVE_LOCK_ERROR if the max number of recursive locks on this mutex was reached
 *NW_MUTEX_NOT_OWNED if this thread does not own the mutex
 */
nw_status nw_mutex_unlock(nw_mutex *mutex);

/**
 *destroys the mutex
 *@param mutex the mutex
 *@return NW_OK on success
 *NW_NOT_INITIALIZED if the mutex was not initialized
 *NW_MUTEX_ALREADY_LOCKED if the mutex is still locked or referenced by another resource
 */
nw_status nw_mutex_destroy(nw_mutex *mutex);

#endif

#endif
