/*
 *  Copyright (C) 2012  Samo Pogacnik
 */

/*
 * The ordered list module, based on strings comparison
 */

#ifndef orderedstr_h
#define orderedstr_h

#ifdef orderedstr_c
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

#ifdef orderedstr_c
/*
 * Here is the PRIVATE stuff (within above ifdef).
 * It is here so we make sure, that the following PRIVATE stuff get included into own source ONLY!
 */

static struct orderedstr_list_element * bisect_orderedstr_list(struct orderedstr_list_header *head, int *compare, const char *string);
static int insert_orderedstr_element(int cmp, struct orderedstr_list_header *head, struct orderedstr_list_element *ref, struct orderedstr_list_element *new);
static int remove_orderedstr_element(struct orderedstr_list_header *head, struct orderedstr_list_element *old);

#endif /*orderedstr_c*/
/*
 * Here continues the PUBLIC stuff, if necessary.
 */

#endif /*orderedstr_h*/

