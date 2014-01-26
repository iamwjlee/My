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
#include "slink.h"


/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */


/* global variables ----------------------------------------------------------- */


/* local variables ------------------------------------------------------------ */


/* macros --------------------------------------------------------------------- */


/* imported function prototypes ----------------------------------------------- */


/* local function prototypes -------------------------------------------------- */


/* global functions ----------------------------------------------------------- */
int slink_count(slink_list_t list)
{
	int						count = 0;

	while(list)
	{
		count++;
		list = list->next;
	}
	return(count);
}

int _slink_contains(slink_list_t list, slink_t *link)
{
	if(link)
	{
		while(list)
		{
			if(list == link)
				return(1);
			list = list->next;
		}
	}
	return(0);
}

void *slink_first(slink_list_t list)
{
	return(list);
}

void *slink_last(slink_list_t list)
{
	while(list)
	{
		if(list->next)
			list = list->next;
		else	break;
	}
	return(list);
}

void _slink_add_front(slink_list_t *list, slink_t *node)
{
	if(list && node)
	{
		slink_t					*first = *list;

		node->next = first;
		*list = node;
	}
}

void _slink_add_back(slink_list_t *list, slink_t *node)
{
	if(list && node)
	{
		slink_t					*last = *list;

		if(last)
		{
			while(last->next)
				last = last->next;
			last->next = node;
		}
		else	*list = node;
	}
}

/* not tested */
void _slink_insert(slink_list_t *list, slink_t *node, slink_comparator compare)
{
	if(list && node)
	{
		slink_t					*ref = *list;

		if(ref)
		{
			if(compare)
			{
				while(ref->next && compare(ref, node) <= 0)
					ref = ref->next;
				node->next = ref->next;
				ref->next = node;
			}
			else
			{
				node->next = ref;
				*list = node;
			}
		}
		else	*list = node;
	}
}

void _slink_remove(slink_list_t *list, slink_t *node)
{
	if(list && node)
	{
		if(*list == node)
			*list = node->next;
		else
		{
			slink_t					*prev;

			for(prev = *list ; prev != NULL ; prev = prev->next)
				if(prev->next == node)
				{
					prev->next = node->next;
					break;
				}
		}
		node->next = NULL;
	}
}

void _slink_delete(slink_list_t *list, slink_t *node)
{
	if(list && node)
	{
		if(*list == node)
		{
			*list = node->next;
			free(node);
		}
		else
		{
			slink_t					*prev;

			for(prev = *list ; prev != NULL ; prev = prev->next)
				if(prev->next == node)
				{
					prev->next = node->next;
					free(node);
					break;
				}
		}
	}
}

void _slink_delete_all(slink_list_t *list)
{
	if(list && *list)
	{
		slink_t					*next, *temp = *list;

		while(temp)
		{
			next = temp->next;
			free(temp);
			temp = next;
		}
		*list = NULL;
	}
}

void *_slink_remove_front(slink_list_t *list)
{
	if(list && *list)
	{
		slink_t					*temp = *list;

		*list = temp->next;
		temp->next = NULL;
		return(temp);
	}
	return(NULL);
}

void *_slink_remove_back(slink_list_t *list)
{
	if(list && *list)
	{
		slink_t					*back = *list;

		if(back->next == NULL)
			*list = NULL;
		else
		{
			slink_t					*temp = *list;

			while(temp->next->next)
				temp = temp->next;
			back = temp->next;
			temp->next = NULL;
		}
		return(back);
	}
	return(NULL);
}

void _slink_bubble_sort(slink_list_t *list, slink_comparator compare)
{
	if(list && *list && compare)
	{
		slink_t				*p, *q, *r, *s = NULL, *temp;

		/* r precedes p and s points to the node up to which comparisons are to be made */
		while(s != (*list)->next)
		{
			r = p = (*list);
			q = p->next;

			while(p != s)
			{
				if(compare(p, q) > 0)
				{
					if(p == (*list))
					{
						temp = q->next;
						q->next = p;
						p->next = temp;
						(*list) = q;
						r = q;
					}
					else
					{
						temp = q->next;
						q->next = p;
						p->next = temp;
						r->next = q;
						r = q;
					}
				}
				else
				{
					r = p;
					p = p->next;
				}
				q = p->next;
				if(q == s)
					s = p;
			}
		}
	}
}

void _slink_selection_sort(slink_list_t *list, slink_comparator compare)
{
	if(list && *list && compare)
	{
		slink_t					*tmp = *list;
		slink_t					*tmp2, *prev, *iLst, *jLst;
		slink_t					*min;

		//swapping the nodes we require previous node (remember this is SLL)
		prev = *list;

		for(iLst = *list ; iLst && iLst->next ; iLst = iLst->next)
		{
			min = iLst;
			for(jLst = iLst->next ; jLst ; jLst = jLst->next)
			{
				//get the minimum node
				if(compare(jLst, min) < 0)
				{
					//mark the minimum node we had encountered so far
					min = jLst;
				}
			}
			//swap the nodes if required
			if(iLst != min)
			{
				tmp = min->next;

				//go find min's previous node (min node can be many nodes away from base node to be swapped)
				for(tmp2 = iLst ; tmp2->next ; tmp2 = tmp2->next)
				{
					if(tmp2->next == min)
						break;
				}

				//check whether node to swapped is in beggining (i.e. header node)
				if(prev != iLst)
				{
					prev->next = min;
				}
				else
				{
					//as we do not have special header node, if the first node and some
					//other node, need to be swapped, then update the list (makes new min node as
					//logical header)
					*list = min;
				}

				//are nodes to be swapped neibgoring nodes?
				if(iLst->next == min)
				{
					//nodes to be swapped are neibhoring nodes, then swap them simply
					min->next = iLst;
					iLst->next = tmp;
				}
				else
				{
					//nodes to be swapped are not neibhor nodes, they are apart so, consider all scenarios
					min->next = iLst->next;
					iLst->next = tmp;
					tmp2->next = iLst;
				}

				//after swapping we've changed our iterator address, so assign correct position to contnue sorting..
				iLst = min;
			}

			//readjust previous node before we move our list pointer
			prev = iLst;
		}
	}
}


/* end of file ---------------------------------------------------------------- */
