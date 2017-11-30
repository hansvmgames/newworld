#ifndef NW_COMMON_TYPE_H
#define NW_COMMON_TYPE_H

#include <stddef.h>
#include <stdint.h>

/**
 *@file contains basic types used by the engine
 */ 

/**
 *defines all status codes
 */
enum nw_status_code{
  NW_OK = 0,
  NW_ERROR,
  NW_ALLOC_ERROR,
  NW_ALREADY_INITIALIZED,
  NW_NOT_INITIALIZED,
  NW_INVALID_ARGUMENT,
  NW_INVALID_STATE,
  NW_EMPTY,
  NW_OUT_OF_BOUNDS,
  NW_IO_ERROR,
  NW_MUTEX_RESOURCE_ERROR,
  NW_MUTEX_ALREADY_LOCKED,
  NW_MUTEX_RECURSIVE_LOCK_ERROR,
  NW_MUTEX_ALREADY_OWNED,
  NW_MUTEX_NOT_OWNED,
  NW_PERMISSION_DENIED,
  NW_LAST_ERROR
};

/**
 *an alias for the status codes
 */
typedef int nw_status;

/**
 *returns a message corresponding to a status code
 *@param status the status code
 *@return a statically allocated message
 */
const char *nw_status_message(nw_status status);

/**
 *a character type capable of holding all unicode codepoints
 */
typedef uint32_t nw_char;

/**
 *a dynamically allocated string type
 */
struct nw_string{

  /**
   *a pointer to the first character in the string
   */
  nw_char *data;

  /**
   *the number of characters in the string
   */
  size_t length;
};

/**
 *initializes a new string with the specified length
 *@param string an uninitialized string
 *@param length the desired length
 *@return NW_OK on success, NW_ALLOC_ERROR if memory allocation fails
 */
nw_status nw_string_init(struct nw_string * string, size_t length);

/**
 *initializes a new string as an empty string
 *@param string an uninitialized string
 */
void nw_string_init_empty(struct nw_string *string);

/**
 *resizes the string
 *if the new length is shorter, the string will be truncated
 *if the new length is longer, unspecified characters will be added at the back
 *if the new length is equal to the current length, nothing will be done
 *@param string the target string
 *@param new_length the desired length
 *@return NW_OK on success, NW_ALLOC_ERROR if memory allocation fails
 */
nw_status nw_string_resize(struct nw_string *string, size_t new_length);

/**
 *concatenates two strings by adding the source string at the back of the destination string
 *if the source string is a zero length string, nothing will be done
 *@param dest the destination string
 *@param src the source string
 *@return NW_OK on success, NW_ALLOC_ERROR if memory allocation fails
 */
nw_status nw_string_concat(struct nw_string *dest, const struct nw_string *src);

/**
 *clears the string, making it into an uninitialized string
 *@param string the string to clear
 */
void nw_string_clear(struct nw_string * string);

#endif
