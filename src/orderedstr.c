/*
 *  Copyright (C) 2012  Samo Pogacnik
 */

/*
 * The ordered list module, based on strings comparison
 */
#ifndef orderedstr_c
#define orderedstr_c
#else
#error Preprocesor macro orderedstr_c conflict!
#endif

#include <stdlib.h>
#include <string.h>

#include "orderedstr.h"

static struct orderedstr_list_element * bisect_orderedstr_list(struct orderedstr_list_header *head, int *compare, const char *string)
{
	int cmp;
	int i, len, m1, m2, mv;
	struct orderedstr_list_element *tmp;

	if ((head == NULL) || (compare == NULL) || (string == NULL))
		return NULL;

	if (head->num_elements == 0) {
		return NULL;
	}

	m1 = 0;
	m2 = head->num_elements;
	len = m2 / 2;

	tmp = head->first;
	cmp = strcmp(string, tmp->string);

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

		cmp = strcmp(string, tmp->string);

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

static int insert_orderedstr_element(int cmp, struct orderedstr_list_header *head, struct orderedstr_list_element *ref, struct orderedstr_list_element *new)
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

int insert_into_orderedstr_list(struct orderedstr_list_header *head, struct orderedstr_list_element *new)
{
	int cmp;
	struct orderedstr_list_element *tmp;

	if ((head == NULL) || (new == NULL) || (new->string == NULL))
		return -1;

	if (head->num_elements == 0) {
		head->first = new;
		new->next = NULL;
		new->previous = NULL;
		head->num_elements++;
		return head->num_elements;
	}

	tmp = bisect_orderedstr_list(head, &cmp, new->string);

	if (cmp == 0)
		return 0;

	return insert_orderedstr_element(cmp, head, tmp, new);
}

struct orderedstr_list_element * select_from_orderedstr_list(struct orderedstr_list_header *head, const char *string)
{
	int cmp;
	struct orderedstr_list_element *tmp;

	tmp = bisect_orderedstr_list(head, &cmp, string);
	if (cmp == 0)
		return tmp;

	return NULL;
}

static int remove_orderedstr_element(struct orderedstr_list_header *head, struct orderedstr_list_element *old)
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

int remove_from_orderedstr_list(struct orderedstr_list_header *head, struct orderedstr_list_element *old)
{
	return remove_orderedstr_element(head, old);
}

