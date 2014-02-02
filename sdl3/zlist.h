/* ------------------------------------------------------------------------------------------------ */
/*																									*/
/*	filename	zlist.h																				*/
/*	description																						*/
/*																									*/
/*	2009-12-09	draft																				*/
/*																									*/
/* ------------------------------------------------------------------------------------------------ */

#ifndef _ZLIST_H_
#define _ZLIST_H_


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
typedef struct zlist_s
{
	struct zlist_s			*next;
} zlist_t;


/* prototypes ------------------------------------------------------------------------------------- */
typedef int (*zlist_compare)(void *x, void *y);


/* variables -------------------------------------------------------------------------------------- */


/* macros ----------------------------------------------------------------------------------------- */
#define ZLIST_INIT						{ NULL }

#define zlist_empty(list)	((list)->next == NULL)

#define zlist_entry(node,type,member)	\
	({ char*n=(char*)(node); type*e=(n)?(type*)((n)-offsetof(type,member)):NULL; e; })

#define zlink_foreach(e,list)							\
	for(e=zlist_entry((list)->next,typeof(*e),zlink);	\
		e!=NULL;										\
		e=zlist_entry(e->zlink.next,typeof(*e),zlink)	)

#define zlink_foreach_safe(e,n,list)					\
	for(e=zlist_entry((list)->next,typeof(*e),zlink),	\
		n=e?e->zlink.next:NULL;							\
		e!=NULL;										\
		e=zlist_entry(n,typeof(*e),zlink),				\
		n=e?e->zlink.next:NULL							)

#define zlist_foreach(e,list,member)					\
	for(e=zlist_entry((list)->next,typeof(*e),member);	\
		e!=NULL;										\
		e=zlist_entry(e->member.next,typeof(*e),member)	)

#define zlist_foreach_safe(e,n,list,member)				\
	for(e=zlist_entry((list)->next,typeof(*e),member),	\
		n=e?e->member.next:NULL;						\
		e!=NULL;										\
		e=zlist_entry(n,typeof(*e),member),				\
		n=e?e->member.next:NULL							)

#define zlink_init(l)					zlist_init(l)
#define zlink_append(l,n)				zlist_append(l,&(n)->zlink)
#define zlink_prepend(l,n)				zlist_prepend(l,&(n)->zlink)
#define zlink_remove(l,n)				zlist_remove(l,&(n)->zlink)
#define zlink_remove_head(l,t)			zlist_entry(zlist_remove_head(l),t,zlink)
#define zlink_remove_tail(l,t)			zlist_entry(zlist_remove_tail(l),t,zlink)


/* functions ------------------------------------------------------------------ */
static inline void	zlist_init(zlist_t *list) { list->next = NULL; }
extern int			zlist_count(zlist_t *list);
extern void			zlist_inverse(zlist_t *list);
//extern int			zlist_contains(zlist_t *list, zlist_t *node);
extern void			zlist_append(zlist_t *list, zlist_t *new);
extern void			zlist_prepend(zlist_t *list, zlist_t *new);
extern void			zlist_remove(zlist_t *list, zlist_t *node);
extern zlist_t*		zlist_remove_head(zlist_t *list);
extern zlist_t*		zlist_remove_tail(zlist_t *list);
extern void			zlist_bubble_sort(zlist_t *list, zlist_compare compare);
extern void			zlist_selection_sort(zlist_t *list, zlist_compare compare);


#ifdef __cplusplus
}
#endif
#endif /* _ZLIST_H_ */
/* end of file ------------------------------------------------------------------------------------ */
