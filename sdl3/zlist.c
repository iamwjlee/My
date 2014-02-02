/* ------------------------------------------------------------------------------------------------ */
/*																									*/
/*	filename	zlist.c																				*/
/*	description																						*/
/*																									*/
/*	2009-11-04	draft																				*/
/*																									*/
/* ------------------------------------------------------------------------------------------------ */

/* compile options -------------------------------------------------------------------------------- */


/* includes --------------------------------------------------------------------------------------- */
//#include <kernel.h>
#include "zlist.h"

/* constants -------------------------------------------------------------------------------------- */


/* types ------------------------------------------------------------------------------------------ */


/* macros ----------------------------------------------------------------------------------------- */
#define headof(l)						((l)->next)


/* prototypes ------------------------------------------------------------------------------------- */


/* variables -------------------------------------------------------------------------------------- */


/* exported variables ----------------------------------------------------------------------------- */


/* exported functions ----------------------------------------------------------------------------- */
int zlist_count(zlist_t *list)
{
	int						count = 0;
	zlist_t					*node;

	if(list && ((node = headof(list)) != NULL))
	{
		do
		{
			count++;
		} while((node = node->next) != NULL);
	}
	return(count);
}

void zlist_inverse(zlist_t *list)
{
	zlist_t					inverse = ZLIST_INIT;
	zlist_t					*node;

	if(list)
	{
		while((node = headof(list)) != NULL)
		{
			headof(list) = node->next;
			node->next = headof(&inverse);
			headof(&inverse) = node;
		}
		memcpy(list, &inverse, sizeof(zlist_t));
	}
}
/*
int zlist_contains(zlist_t *list, zlist_t *node)
{
	zlist_t					*check;

	if(list && check && ((check = headof(list)) != NULL))
	{
		do
		{
			if(check == node)	return(1);
		} while((check = check->next) != NULL);
	}
	return(0);
}
*/
void zlist_append(zlist_t *list, zlist_t *new)
{
	zlist_t					*tail = list;

	if(((tail = list) != NULL) && new)
	{
		while(tail->next)
			tail = tail->next;
		tail->next = new;
	}
}

void zlist_prepend(zlist_t *list, zlist_t *new)
{
	if(list && new)
	{
		new->next = headof(list);
		headof(list) = new;
	}
}

void zlist_remove(zlist_t *list, zlist_t *node)
{
	zlist_t					*check = list;

	if(check && node)
	{
		do
		{
			if(check->next == node)
			{
				check->next = node->next;
				node->next = NULL;
				break;
			}
		} while((check = check->next) != NULL);
	}
}

zlist_t *zlist_remove_head(zlist_t *list)
{
	zlist_t					*head;

	if(list && ((head = headof(list)) != NULL))
	{
		headof(list) = head->next;
		head->next = NULL;
		return(head);
	}
	return(NULL);
}

zlist_t *zlist_remove_tail(zlist_t *list)
{
	zlist_t					*node, *tail;

	if(list && ((node = headof(list)) != NULL))
	{
		if(node->next == NULL)
		{
			headof(list) = NULL;
			return(node);
		}
		while(node->next->next != NULL)
			node = node->next;
		tail = node->next;
		node->next = NULL;
		return(tail);
	}
	return(NULL);
}

void zlist_bubble_sort(zlist_t *list, zlist_compare compare)
{
	if(list && headof(list) && compare)
	{
		zlist_t					*x, *y, *r, *s = NULL, *temp;

		/* r precedes x and s points to the node up to which comparisons are to be made */
		while(s != headof(list)->next)
		{
			r = x = headof(list);
			y = x->next;

			while(x != s)
			{
				if(compare(x, y) > 0)
				{
					if(x == headof(list))
					{
						temp = y->next;
						y->next = x;
						x->next = temp;
						headof(list) = y;
						r = y;
					}
					else
					{
						temp = y->next;
						y->next = x;
						x->next = temp;
						r->next = y;
						r = y;
					}
				}
				else
				{
					r = x;
					x = x->next;
				}
				y = x->next;
				if(y == s)
					s = x;
			}
		}
	}
}

void zlist_selection_sort(zlist_t *list, zlist_compare compare)
{
	zlist_t					*prev;

	if(list && ((prev = headof(list)) != NULL) && compare)
	{
		zlist_t					*iLst, *jLst;

		for(iLst = headof(list) ; iLst && iLst->next ; iLst = iLst->next)
		{
			zlist_t					*min = iLst;

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
				zlist_t					*tmp = min->next;
				zlist_t					*tmp2;

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
					headof(list) = min;
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
