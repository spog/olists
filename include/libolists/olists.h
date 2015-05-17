/*
 * The public API of the "olists" library
 *
 * Copyright (C) 2015 Samo Pogacnik <samo_pogacnik@t-2.net>
 * All rights reserved.
 *
 * This file is part of the "olists" software project.
 * This file is provided under the terms of the BSD 3-Clause license,
 * available in the LICENSE file of the "olists" software project.
*/

#ifndef olists_h
#define olists_h

/*
 * The "orderedstr" part
 */

struct orderedstr_list_element {
	const char *string;
	void *priv;
	struct orderedstr_list_element *next;
	struct orderedstr_list_element *previous;
};

struct orderedstr_list_header {
	int num_elements;
	struct orderedstr_list_element *first;
};

extern int insert_into_orderedstr_list(struct orderedstr_list_header *head, struct orderedstr_list_element *new);
extern struct orderedstr_list_element * select_from_orderedstr_list(struct orderedstr_list_header *head, const char *string);
extern int remove_from_orderedstr_list(struct orderedstr_list_header *head, struct orderedstr_list_element *old);

/*
 * The "orderedmem" part
 */

struct orderedmem_list_element {
	void *mem;
	void *priv;
	struct orderedmem_list_element *next;
	struct orderedmem_list_element *previous;
};

struct orderedmem_list_header {
	int mem_size;
	int num_elements;
	struct orderedmem_list_element *first;
};

extern int insert_into_orderedmem_list(struct orderedmem_list_header *head, struct orderedmem_list_element *new);
extern struct orderedmem_list_element * select_from_orderedmem_list(struct orderedmem_list_header *head, void *mem);
extern int remove_from_orderedmem_list(struct orderedmem_list_header *head, struct orderedmem_list_element *old);

#endif /*olists_h*/

