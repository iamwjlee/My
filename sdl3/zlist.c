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
#define print(...)  printf(__VA_ARGS__)


/* prototypes ------------------------------------------------------------------------------------- */


/* variables -------------------------------------------------------------------------------------- */


/* exported variables ----------------------------------------------------------------------------- */


/* exported functions ----------------------------------------------------------------------------- */
zlist_t* zlist_first(zlist_t *list)
{
	zlist_t					*node;

	if(list && ((node = headof(list)) != NULL))
	{
		return(node);
	}
	return(NULL);
}

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

/* ---------------------------------------------------------------- */
/*
http://www.mcs.anl.gov/~kazutomo/list/


*/

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})


int  t_container(void) {
      struct s {
          int a;
          int b;
          int c;
    } v;

     print("container (&v): 0x%p\n", &v);
     print("container of a: 0x%p\n", container_of(&v.a, struct s, a));
     print("container of b: 0x%p\n", container_of(&v.b, struct s, b));
     print("container of c: 0x%p\n", container_of(&v.c, struct s, c));
 
     return 0;
 }
 
#if 1
typedef struct 
{
	zlist_t					zlink;
	int a;
}test_list_t;
static zlist_t  Zlist;

int t_zlist(void)
{
	int cnt;
	test_list_t *test01;
	test_list_t *tmp;

	zlink_init(&Zlist);

	test01=malloc(sizeof(test_list_t));
	memset(test01,0,sizeof(test_list_t));
	test01->a=11;
	zlink_append(&Zlist,  test01);

	
	test01=malloc(sizeof(test_list_t));
	memset(test01,0,sizeof(test_list_t));
	test01->a=12;
	zlink_append(&Zlist,  test01);

	
	test01=malloc(sizeof(test_list_t));
	memset(test01,0,sizeof(test_list_t));
	test01->a=13;
	zlink_append(&Zlist,  test01);

	 print("show list\n"); 	 
	zlink_foreach(tmp,&Zlist)
		{
	 	print("test01[0x%x] test01->a=%d   Zlist[%x] Zlist->next[%x] \n",(unsigned int)tmp,tmp->a,Zlist,(unsigned int)Zlist.next  );
	 	print("    0x%x\n",(unsigned int)tmp->zlink.next);
	 	}	


	tmp=(test_list_t *)zlist_first(&Zlist);
	print(" tmp [%d]\n",tmp->a); 
	cnt=8;

	// channel change test
	while(--cnt)
	{
	
		tmp=zlist_entry(tmp->zlink.next, test_list_t,zlink );
		if(tmp==NULL) 
		{
			tmp=(test_list_t *)zlist_first(&Zlist);
			
		}	
		print(" tmp [%d]\n",tmp->a); 

	}

	print("delete one list\n");		
	 zlink_foreach(tmp,&Zlist)
	 {
		 if(tmp->a==12)
			 zlink_remove(&Zlist, tmp);
 
	}  
	 print("show list\n"); 	 
	zlink_foreach(tmp,&Zlist)
		{
	 	print("tmp[0x%x] tmp->a=%d   Zlist[%x] Zlist->next[%x] \n",(unsigned int)tmp,tmp->a,Zlist,(unsigned int)Zlist.next  );
	 	print("    0x%x\n",(unsigned int)tmp->zlink.next);
	 	}	

	
	print("free list\n");
	while((tmp = (test_list_t *)zlist_remove_head(&Zlist)) != NULL){
		print("tmp[0x%x] freed\n",(unsigned int)tmp);
		free(tmp);
	} 
	print("Zlist[%x],Zlist.next[%x]\n",Zlist,(unsigned int)Zlist.next);
	
	print(" count=%d\n", zlist_count(&Zlist));

	
	return 0;

}

#endif


/* end of file ---------------------------------------------------------------- */
