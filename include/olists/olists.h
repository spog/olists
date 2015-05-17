/*
 *  Copyright (C) 2015  Samo Pogacnik
 */

/*
 * The olists module
 */

#ifndef olists_h
#define olists_h

#ifdef olists_c
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

EXTERN int olists(void);

#ifdef olists_c
/*
 * Here is the PRIVATE stuff (within above ifdef).
 * It is here so we make sure, that the following PRIVATE stuff get included into own source ONLY!
 */

#endif /*olists_c*/
/*
 * Here continues the PUBLIC stuff, if necessary.
 */

#endif /*olists_h*/

