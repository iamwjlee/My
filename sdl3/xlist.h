/* ------------------------------------------------------------------------------------------------ */
/*																									*/
/*	filename	xlist.h																				*/
/*	description	Double-Linked List																	*/
/*																									*/
/*	2010-01-26	draft																				*/
/*																									*/
/* ------------------------------------------------------------------------------------------------ */

#ifndef _XLIST_H_
#define _XLIST_H_


#ifdef __cplusplus
extern "C" {
#endif

/* includes --------------------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* constants -------------------------------------------------------------------------------------- */


/* types ------------------------------------------------------------------------------------------ */
typedef struct xnode_s
{
	struct xnode_s			*next;
	struct xnode_s			*prev;
} xnode_t;

typedef struct xlist_s
{
	struct xnode_s			*head;
	struct xnode_s			*tail;
} xlist_t;


/* prototypes ------------------------------------------------------------------------------------- */
typedef int (*xlist_compare)(void *x, void *y);


/* variables -------------------------------------------------------------------------------------- */


/* macros ----------------------------------------------------------------------------------------- */
#define XLIST_INIT			{ NULL, NULL }
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define xlist_empty(list)	((list)->head == NULL)

#define xlist_entry(node,type,member)	\
	({ char*n=(char*)(node); type*e=(n)?(type*)((n)-offsetof(type,member)):NULL; e; })

#define xlink_foreach(e,list)							\
	for(e=xlist_entry((list)->head,typeof(*e),xlink);	\
		e!=NULL;										\
		e=xlist_entry(e->xlink.next,typeof(*e),xlink)	)

#define xlink_foreach_safe(e,n,list)					\
	for(e=xlist_entry((list)->head,typeof(*e),xlink),	\
		n=e?e->xlink.next:NULL;							\
		e!=NULL;										\
		e=xlist_entry(n,typeof(*e),xlink),				\
		n=e?e->xlink.next:NULL							)

#define xlist_foreach(e,list,member)					\
	for(e=xlist_entry((list)->head,typeof(*e),member);	\
		e!=NULL;										\
		e=xlist_entry(e->member.next,typeof(*e),member)	)

#define xlist_foreach_safe(e,n,list,member)				\
	for(e=xlist_entry((list)->head,typeof(*e),member),	\
		n=e?e->member.next:NULL;						\
		e!=NULL;										\
		e=xlist_entry(n,typeof(*e),member),				\
		n=e?e->member.next:NULL							)

#define xlink_init(l)					xlist_init(l)
#define xlink_append(l,n)				xlist_append(l,&(n)->xlink)
#define xlink_prepend(l,n)				xlist_prepend(l,&(n)->xlink)
#define xlink_remove(l,n)				xlist_remove(l,&(n)->xlink)
#define xlink_remove_head(l,t)			xlist_entry(xlist_remove_head(l),t,xlink)
#define xlink_remove_tail(l,t)			xlist_entry(xlist_remove_tail(l),t,xlink)


/* functions ------------------------------------------------------------------ */
static inline void	xlist_init(xlist_t *list) { memset(list, 0, sizeof(xlist_t)); }
extern int			xlist_count(xlist_t *list);
extern void			xlist_append(xlist_t *list, xnode_t *new);
extern void			xlist_prepend(xlist_t *list, xnode_t *new);
extern void			xlist_remove(xlist_t *list, xnode_t *node);
extern xnode_t*		xlist_remove_head(xlist_t *list);
extern xnode_t*		xlist_remove_tail(xlist_t *list);
extern void			xlist_bubble_sort(xlist_t *list, xlist_compare compare);
extern void			xlist_selection_sort(xlist_t *list, xlist_compare compare);
extern void			xlist_merge(xlist_t *list1, xlist_t *list2);


#ifdef __cplusplus
}
#endif
#endif /* _XLIST_H_ */
/* end of file ------------------------------------------------------------------------------------ */
