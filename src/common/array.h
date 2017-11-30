#ifndef NW_COMMON_ARRAY_H
#define NW_COMMON_ARRAY_H

#include "collection.h"
#include "type.h"

#include <stddef.h>

/**
 *an incomplete type for a general purpose array
*/
struct nw_array;

/**
 *an alias for a reference to an array
 */
typedef struct nw_array * nw_array_ref;

/**
 *an alias for a reference to a constant array
 */
typedef const struct nw_array * nw_array_cref;

/**
 *a struct containing policy callbacks for an array
 */
struct nw_array_policy{
  nw_element_destroy destroy;
};

/**
 *the default array initial size
 */
extern const size_t mw_default_array_initial_size;

/**
 *the default array policy
 */
extern const struct nw_array_policy nw_default_array_policy;

/**
 *creates an new array
 *@param dest the reference to initialize the array in
 *@param initial_size the initial size of the array, zero for default
 *@param policy a pointer to a policy struct or NULL for the default policy
 *@return NW_OK on success, NW_ALLOC_ERROR when memory allocation fails
 */
nw_status nw_array_create(nw_array_ref *dest, size_t initial_size, const struct nw_array_policy *policy);

/**
 *ensures the size of this array is large enough to keep the desired capacity
 *@param array the target array
 *@param capacity the minimum desired size
 *@return NW_OK on success, NW_ALLOC_ERROR when memory allocation fails
 */
nw_status nw_array_ensure(nw_array_ref array, size_t capacity);

/**
 *adds a value on the back of the array
 *@param array the array
 *@param value the value to add
 *@return NW_OK on success, NW_ALLOC_ERROR when memory allocation fails
 */
nw_status nw_array_push_back(nw_array_ref array, nw_element value);

/**
 *removes a value from the back of the array
 *@param array the array
 *@return NW_OK on success, NW_EMPTY when the array has no more values
 */
nw_status nw_array_pop_back(nw_array_ref array);

/**
 *returns the length of the array
 *@param array the array
 *@return the length of the array
 */
size_t nw_array_length(nw_array_cref array);

/**
 *returns the value at the specified index in the array
 *@param array the array
 *@param index the index
 *@return the value
 */
nw_element nw_array_at(nw_array_cref array, size_t index);

/**
 *fetches the value at the specified index in the array
 *@param array the array
 *@param index the index
 *@param result a pointer to store the result in
 *@return NW_OK if the value was found, NW_OUT_OF_BOUNDS if the index is out of bounds
 */
nw_status nw_array_at_checked(nw_array_cref array, size_t index, nw_element *result);

/**
 *destroys the array
 *@param src the address of the array
 */
void nw_array_destroy(nw_array_ref *src);

#endif
