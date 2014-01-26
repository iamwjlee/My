/********************************************************************************/
/*																				*/
/* File name:	slink.c															*/
/*																				*/
/* Description:	GxLIB: Singly Linked List										*/
/*																				*/
/* COPYRIGHT (C) Genix InfoComm 2008											*/
/*																				*/
/* Date			Modification									Name			*/
/* ----			------------									----			*/
/* 2008-06-16	draft											Jake			*/
/*																				*/
/********************************************************************************/

/* includes ------------------------------------------------------------------- */
#include <stdlib.h>
#include "dlink.h"


/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */


/* global variables ----------------------------------------------------------- */


/* local variables ------------------------------------------------------------ */


/* macros --------------------------------------------------------------------- */


/* imported function prototypes ----------------------------------------------- */


/* local function prototypes -------------------------------------------------- */


/* global functions ----------------------------------------------------------- */
void _dlink_append(dlink_list_t *list, dlink_t *link)
{
	dlink_t					*first = *list;

	link->next = NULL;
	if(first != NULL)
	{
		dlink_t					*last = first->prev;

		link->prev = last;
		last->next = first->prev = link;
	}
	else	*list = link->prev = link;
}

void _dlink_prepend(dlink_list_t *list, dlink_t *link)
{
	dlink_t					*first = *list;

	link->next = first;
	if(first != NULL)
	{
		link->prev = first->prev;
		first->prev = link;
	}
	else	link->prev = link;
	*list = link;
}

void _dlink_append_list(dlink_list_t *list1, dlink_list_t list2)
{
	dlink_t					*first1	= *list1;
	dlink_t					*first2	= list2;

	if(first1 && first2)
	{
		dlink_t					*last1	= first1->prev;
		dlink_t					*last2	= first2->prev;

		first1->prev	= last2;
		last1->next		= first2;
		first2->prev	= last1;
	}
	else if(first2)
	{
		*list1 = first2;
	}
}

void _dlink_prepend_list(dlink_list_t *list1, dlink_list_t list2)
{
	dlink_t					*first1	= *list1;
	dlink_t					*first2	= list2;

	if(first1 && first2)
	{
		dlink_t					*last1	= first1->prev;
		dlink_t					*last2	= first2->prev;

		first2->prev	= last1;
		last2->next		= first1;
		first1->prev	= last2;
	}

	if(first2)
		*list1 = first2;
}

void _dlink_insert_list(dlink_list_t *list1, dlink_list_t list2, dlink_t *link)
{
	dlink_t					*first1 = *list1;
	dlink_t					*first2 = list2;

	if(first1 && first2)
	{
		dlink_t					*last2 = first2->prev;

		if(!link)
			_dlink_append_list(list1, list2);
		else if(link == first1)
			_dlink_prepend_list(list1, list2);
		else
		{
			dlink_t				*prev_of_link = link->prev;

			first2->prev = prev_of_link;
			prev_of_link->next = first2;

			last2->next = link;
			link->prev	= last2;
		}
	}
}

void _dlink_insert_before(dlink_t *ref, dlink_t *link)
{
	dlink_t					*prev_of_ref	= ref->prev;
	dlink_t					*prev_of_link	= link->prev;
	dlink_t					*next_of_link	= link->next;
	dlink_t					*first_of_list	= NULL;

	if(	(link != ref) &&
		(!next_of_link || (next_of_link && (link != ref->prev))))
	{
		if(!next_of_link)	/* last of list */
			for(first_of_list = link->prev; first_of_list->prev != link; first_of_list = first_of_list->prev);
			if(first_of_list == ref)
				first_of_list = link;

		if(prev_of_ref && prev_of_ref->next)
			prev_of_ref->next = link;

		if(link != prev_of_ref)
			link->prev = prev_of_ref;

		ref->prev = link;
		link->next = ref;

		if(prev_of_link && prev_of_link->next)
			prev_of_link->next = next_of_link;
		if(next_of_link)
			next_of_link->prev = prev_of_link;
		if(first_of_list)
			first_of_list->prev = prev_of_link;
	}
}

void _dlink_insert_after(dlink_t *ref, dlink_t *link)
{
	dlink_t					*next_of_ref	= ref->next;
	dlink_t					*prev_of_link	= link->prev;
	dlink_t					*next_of_link	= link->next;
	dlink_t					*first_of_list	= NULL;
	dlink_t					*last_of_list	= NULL;

	if((link != ref) && (link != ref->next))
	{
		if(!next_of_ref)		/* ref == last of list */
		{
			if(prev_of_link == ref)	/* link == first_of_list */
				first_of_list = next_of_link;
			else
				for(first_of_list = ref->prev; first_of_list->prev != ref; first_of_list = first_of_list->prev);

			last_of_list = link;
		}
		else if(!next_of_link)	/* link == last of list */
		{
			for(first_of_list = link->prev; first_of_list->prev != link; first_of_list = first_of_list->prev);
			last_of_list = prev_of_link;
		}

		if(next_of_ref)
			next_of_ref->prev = link;

		if(prev_of_link && prev_of_link->next)
			prev_of_link->next = next_of_link;
		if(next_of_link)
			next_of_link->prev = prev_of_link;

		if(first_of_list)
			first_of_list->prev = last_of_list;

		link->next	= next_of_ref;
		ref->next	= link;
		link->prev	= ref;
	}
}

int _dlink_contains(dlink_list_t list, dlink_t *link)
{
	if(!link->prev && !link->next)
		return(0);

	while(list)
	{
		if(list == link)
			return(1);
		list = list->next;
	}
	return(0);
}

int _dlink_count(dlink_list_t list)
{
	int						count = 0;

	while(list)
	{
		count++;
		list = list->next;
	}
	return(count);
}

void _dlink_remove(dlink_t **list, dlink_t *link)
{
	dlink_t					*next = link->next;
	dlink_t					*prev = link->prev;

	if(next)
		next->prev = prev;
	else	(*list)->prev = prev;

	if(link == *list)
		*list = next;
	else	prev->next = next;

	link->next = link->prev = NULL;
}

void _dlink_sort(dlink_list_t *list, dlink_comparator compare)
{
	if((list != NULL) && ((*list) != NULL) && (compare != NULL))
	{
		dlink_t					*first = (dlink_t *)*list;
		dlink_t					*last = ((dlink_t *)*list)->prev;
		dlink_t					*x, *y, *next;

		for(x = first->next ; x != NULL ; x = next)
		{
			dlink_t					*prev = x->prev;

			for(y = prev ; y != last ; y = y->prev)
				if(compare(x, y) >= 0)
					break;

			next = x->next;
			if(y != prev)
			{
				if(next)	next->prev = prev;
				else		(*list)->prev = prev;
				prev->next = next;

				if(y == last)	/* insert x at front of list */
				{
					x->next = *list;
					x->prev = (*list)->prev;
					(*list)->prev = x;
					*list = x;
				}
				else			/* insert x after y */
				{
					x->next = y->next;
					x->prev = y;
					y->next->prev = x;
					y->next = x;
				}
			}
		}
	}
}


/* end of file ---------------------------------------------------------------- */
