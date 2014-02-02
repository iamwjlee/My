/* ------------------------------------------------------------------------------------------------ */
/*																									*/
/*	filename	xlist.c																				*/
/*	description	Double-Linked List																	*/
/*																									*/
/*	2010-01-26	draft																				*/
/*																									*/
/* ------------------------------------------------------------------------------------------------ */

/* compile options -------------------------------------------------------------------------------- */


/* includes --------------------------------------------------------------------------------------- */


#include "xlist.h"

/* constants -------------------------------------------------------------------------------------- */


/* types ------------------------------------------------------------------------------------------ */


/* macros ----------------------------------------------------------------------------------------- */


/* prototypes ------------------------------------------------------------------------------------- */


/* variables -------------------------------------------------------------------------------------- */


/* exported variables ----------------------------------------------------------------------------- */


/* exported functions ----------------------------------------------------------------------------- */
int xlist_count(xlist_t *list)
{
	int						count = 0;
	xnode_t					*node;

	if(list && ((node = list->head) != NULL))
	{
		do
		{
			count++;
		} while((node = node->next) != NULL);
	}
	return(count);
}

void xlist_append(xlist_t *list, xnode_t *new)
{
	if(list && new)
	{
		//ASSERT(!new->next && !new->prev);
		if(!list->head)	/* empty list */
		{
			list->head = new;
		}
		else
		{
			list->tail->next = new;
			new->prev = list->tail;
		}
		list->tail = new;
	}
}

void xlist_prepend(xlist_t *list, xnode_t *new)
{
	if(list && new)
	{
		//ASSERT(!new->next && !new->prev);
		if(!list->head)	/* empty list */
		{
			list->tail = new;
		}
		else
		{
			new->next = list->head;
			list->head->prev = new;
		}
		list->head = new;
	}
}

void xlist_remove(xlist_t *list, xnode_t *node)
{
	xnode_t					*exist;
	xnode_t					*prev, *next;

	if(list && node)
	{
		for(exist = list->head ; exist != NULL ; exist = exist->next)
			if(node == exist)
				break;
		if(!exist)	return;

		if((prev = exist->prev) != NULL)
			prev->next = exist->next;
		else	list->head = exist->next;

		if((next = exist->next) != NULL)
			next->prev = exist->prev;
		else	list->tail = exist->prev;

		memset(node, 0, sizeof(xnode_t));
	}
}

xnode_t *xlist_remove_head(xlist_t *list)
{
	xnode_t					*head = NULL;

	if(list && ((head = list->head) != NULL))
	{
		list->head = head->next;
		if(head->next)
			head->next->prev = NULL;
		else	list->tail = NULL;
	}
	return(head);
}

xnode_t *xlist_remove_tail(xlist_t *list)
{
	xnode_t					*tail = NULL;

	if(list && ((tail = list->tail) != NULL))
	{
		list->tail = tail->prev;
		if(tail->prev)
			tail->prev->next = NULL;
		else	list->head = NULL;
	}
	return(tail);
}

void xlist_bubble_sort(xlist_t *list, xlist_compare compare)
{
	if(list && compare && list->head)
	{
		xnode_t					*x, *y, *s = NULL;
		xnode_t					*prev_x;

		while(s != list->head)
		{
			x		= list->head;
			y		= x->next;
			prev_x	= x->prev;

			while(x->next != s)
			{
				if(compare(x, y) > 0)
				{
					xnode_t					*next_y = y->next;

					if(prev_x)	prev_x->next = y;
					else		list->head = y;
					y->prev	= prev_x;

					y->next	= x;
					x->prev	= y;

					x->next	= next_y;
					if(next_y)	next_y->prev = x;
					else		list->tail = x;
					prev_x = y;
				}
				else
				{
					prev_x	= x;
					x		= x->next;
				}
				y = x->next;
			}
			s = x;
		}
	}
}

void xlist_selection_sort(xlist_t *list, xlist_compare compare)
{
	if(list && compare && list->head)
	{
		xnode_t					*x, *y;

		for(x = list->head; x && x->next; x = x->next)
		{
			xnode_t					*min = x;

			for(y = x->next; y; y = y->next)
			{
				if(compare(y, min) < 0)
					min = y;
			}

			if(x != min)	/* swap */
			{
				xnode_t					*p_min = min->prev, *n_min = min->next;
				xnode_t					*prev_x = x->prev, *next_x = x->next;

				if(prev_x)	prev_x->next = min;
				else		list->head = min;
				min->prev = prev_x;

				if(n_min)	n_min->prev = x;
				else		list->tail = x;
				x->next = n_min;

				if(next_x == min)
				{
					min->next = x;
					x->prev = min;
				}
				else
				{
					min->next		= next_x;
					next_x->prev	= min;

					p_min->next	= x;
					x->prev			= p_min;
				}
				x = min;
			}
		}
	}
}

void xlist_merge(xlist_t *list1, xlist_t *list2)
{
	if(list1 && list2)
	{
		if(list1->head)
		{
			if(list2->head)
			{
				list1->tail->next = list2->head;
				list2->head->prev = list1->tail;
				list1->tail = list2->tail;
			}
		}
		else	memcpy(list1, list2, sizeof(xlist_t));
	}
}


/* end of file ---------------------------------------------------------------- */
