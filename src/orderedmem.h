/*
 *  Copyright (C) 2012  Samo Pogacnik
 */

/*
 * The ordered list module, based on memory areas comparison
 */

#ifndef orderedmem_h
#define orderedmem_h

#ifdef orderedmem_c
/* PRIVATE usage of the PUBLIC part. */
#	undef EXTERN
#	define EXTERN
#else
/* PUBLIC usage of the PUBLIC part. */
#	undef EXTERN
#	define EXTERN extern
#endif
/*
 * Here starts the PUBLIC stuff:
 *	Enter PUBLIC declarations using EXTERN!
 */
#include <libolists/olists.h>

#ifdef orderedmem_c
/*
 * Here is the PRIVATE stuff (within above ifdef).
 * It is here so we make sure, that the following PRIVATE stuff get included into own source ONLY!
 */

static struct orderedmem_list_element * bisect_orderedmem_list(struct orderedmem_list_header *head, int *compare, void *mem);
static int insert_orderedmem_element(int cmp, struct orderedmem_list_header *head, struct orderedmem_list_element *ref, struct orderedmem_list_element *new);
static int remove_orderedmem_element(struct orderedmem_list_header *head, struct orderedmem_list_element *old);

#endif /*orderedmem_c*/
/*
 * Here continues the PUBLIC stuff, if necessary.
 */

#endif /*orderedmem_h*/

