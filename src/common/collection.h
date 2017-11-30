#ifndef NW_COMMON_COLLECTION_H
#define NW_COMMON_COLLECTION_H

#include "type.h"

/**
 *a type that can contain any pointer to an element
*/
typedef void * nw_element;

/**
 * describes a callback function to destroy an element
 */
typedef nw_status (*nw_element_destroy)(nw_element *);

#endif
