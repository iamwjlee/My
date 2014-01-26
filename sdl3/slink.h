/********************************************************************************/
/*																				*/
/* File name:	gxlib/list/slink.h												*/
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
#ifndef _GxLIB_SLINK_H_
#define _GxLIB_SLINK_H_


#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------- */


/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */
typedef int								(*slink_comparator)(void *x, void *y);

typedef struct slink_s
{
	struct slink_s			*next;
} slink_t, *slink_list_t;

typedef struct
{
	slink_t					slink;
} fake_slink_t;


/* variables ------------------------------------------------------------------ */


/* macros --------------------------------------------------------------------- */
#define SINGLE_LINKED_LIST				slink_t	slink;
#define SLINK(p)						((fake_slink_t*)p)

#define slink_foreach(n, list)												\
	for(n = (typeof(n))(list) ;												\
		n != NULL ;															\
		n = (typeof(n))((n)->slink.next))

#define slink_foreach_safe(n, s, list)										\
	for(n = (typeof(n))(list),												\
		s = (typeof(s))((n) ? ((n)->slink.next) : NULL) ;					\
		n != NULL ;															\
		n = (typeof(n))(s),													\
		s = (typeof(s))((n) ? ((n)->slink.next) : NULL) )

#define slink_contains(l, n)				_slink_contains((l), &(n)->slink)
#define slink_add_back(l, n)				_slink_add_back(&(l), &(n)->slink)
#define slink_add_front(l, n)				_slink_add_front(&(l), &(n)->slink)
#define slink_insert(l,n,f)					_slink_insert(&(l), &(n)->slink, f)	/* not tested */
#define slink_remove(l, n)					_slink_remove(&(l), &(n)->slink)
#define slink_delete(l, n)					_slink_delete(&(l), &(n)->slink)
#define slink_delete_all(l)					_slink_delete_all(&(l))
#define slink_remove_front(l)				_slink_remove_front(&(l))
#define slink_remove_back(l)				_slink_remove_back(&(l))
#define slink_next(n)						((n)?(void*)((n)->slink.next):NULL)
#define slink_sort(l,c)						_slink_bubble_sort(&(l), c)
#define slink_bubble_sort(l,c)				_slink_bubble_sort(&(l), c)
#define slink_selection_sort(l,c)			_slink_selection_sort(&(l), c)

#define slink_append(l, n)					slink_add_back(l, n)
#define slink_prepend(l, n)					slink_add_front(l, n)


/* functions ------------------------------------------------------------------ */
extern int	slink_count(slink_list_t list);
extern int	_slink_contains(slink_list_t list, slink_t *link);
extern void	*slink_first(slink_list_t list);
extern void *slink_last(slink_list_t list);
extern void	_slink_add_front(slink_list_t *list, slink_t *node);
extern void	_slink_add_back(slink_list_t *list, slink_t *node);
extern void _slink_insert(slink_list_t *list, slink_t *node, slink_comparator compare);
extern void	_slink_remove(slink_list_t *list, slink_t *node);
extern void _slink_delete(slink_list_t *list, slink_t *node);
extern void _slink_delete_all(slink_list_t *list);
extern void *_slink_remove_front(slink_list_t *list);
extern void *_slink_remove_back(slink_list_t *list);
extern void _slink_bubble_sort(slink_list_t *list, slink_comparator compare);

#ifdef __cplusplus
}
#endif
#endif /* _GxLIB_SLINK_H_ */
/* end of file ---------------------------------------------------------------- */
