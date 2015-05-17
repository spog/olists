/*
 *  Copyright (C) 2012  Samo Pogacnik
 */

/*
 * The ordered list module, based on memory areas comparison
 */
#ifndef orderedmem_c
#define orderedmem_c
#else
#error Preprocesor macro orderedmem_c conflict!
#endif

#include <stdlib.h>
#include <string.h>

#include "orderedmem.h"

static struct orderedmem_list_element * bisect_orderedmem_list(struct orderedmem_list_header *head, int *compare, void *mem)
{
	int cmp;
	int i, len, m1, m2, mv;
	struct orderedmem_list_element *tmp;

	if ((head == NULL) || (compare == NULL) || (mem == NULL))
		return NULL;

	if (head->num_elements == 0) {
		return NULL;
	}

	m1 = 0;
	m2 = head->num_elements;
	len = m2 / 2;

	tmp = head->first;
	cmp = memcmp(mem, tmp->mem, head->mem_size);

	while (len > 0) {
		if (cmp > 0) {
			if (tmp->next == NULL) break /*while*/;
			mv = 0;
			for (i = 0; i < len; i++) {
				if (tmp->next == NULL) break /*for*/;
				else tmp = tmp->next;
				mv++;
			}
		} else
		if (cmp < 0) {
			if (tmp->previous == NULL) break /*while*/;
			mv = 0;
			for (i = 0; i < len; i++) {
				if (tmp->previous == NULL) break /*for*/;
				else tmp = tmp->previous;
				mv--;
			}
		} else { /*(cmp == 0) - exact key match!*/
			break /*while*/;
		}

		cmp = memcmp(mem, tmp->mem, head->mem_size);

		if (cmp > 0) {
			if (mv > 0) m1 += mv;
			else m1 = m2 + mv;
		} else
		if (cmp < 0) {
			if (mv < 0) m2 += mv;
			else m2 = m1 + mv;
		} else { /*(cmp == 0) - exact key match!*/
			break /*while*/;
		}

		len = (m2 - m1) / 2;
	}

	*compare = cmp;
	return tmp;
}

static int insert_orderedmem_element(int cmp, struct orderedmem_list_header *head, struct orderedmem_list_element *ref, struct orderedmem_list_element *new)
{
	if (cmp == 0)
		return 0;

	if ((head == NULL) || (new == NULL) || (ref == NULL))
		return -1;

	if (cmp > 0) {
		if (ref->next != NULL) {
			new->next = ref->next;
			new->next->previous = new;
			new->previous = ref;
			ref->next = new;
		} else {
			new->next = NULL;
			new->previous = ref;
			ref->next = new;
		}
	} else { /*(cmp < 0)*/
		if (ref->previous != NULL) {
			new->previous = ref->previous;
			new->previous->next = new;
			new->next = ref;
			ref->previous = new;
		} else {
			new->previous = NULL;
			new->next = ref;
			ref->previous = new;
			head->first = new;
		}
	}
	head->num_elements++;
	return head->num_elements;
}

int insert_into_orderedmem_list(struct orderedmem_list_header *head, struct orderedmem_list_element *new)
{
	int cmp;
	struct orderedmem_list_element *tmp;

	if ((head == NULL) || (new == NULL) || (new->mem == NULL))
		return -1;

	if (head->num_elements == 0) {
		head->first = new;
		new->next = NULL;
		new->previous = NULL;
		head->num_elements++;
		return head->num_elements;
	}

	tmp = bisect_orderedmem_list(head, &cmp, new->mem);

	if (cmp == 0)
		return 0;

	return insert_orderedmem_element(cmp, head, tmp, new);
}

struct orderedmem_list_element * select_from_orderedmem_list(struct orderedmem_list_header *head, void *mem)
{
	int cmp;
	struct orderedmem_list_element *tmp;

	tmp = bisect_orderedmem_list(head, &cmp, mem);
	if (cmp == 0)
		return tmp;

	return NULL;
}

static int remove_orderedmem_element(struct orderedmem_list_header *head, struct orderedmem_list_element *old)
{
	if (head == NULL)
		return -1;

	if (old == NULL)
		return head->num_elements;

	if (old->previous == NULL) { /*first*/
		head->first = old->next;
		if (old->next != NULL) /*not last*/
			old->next->previous = NULL;
	} else {
		old->previous->next = old->next;
		if (old->next != NULL) /*not last*/
			old->next->previous = old->previous;
	}

	head->num_elements--;
	return head->num_elements;
}

int remove_from_orderedmem_list(struct orderedmem_list_header *head, struct orderedmem_list_element *old)
{
	return remove_orderedmem_element(head, old);
}

