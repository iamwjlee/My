/********************************************************************************/
/*																				*/
/* File name:	gxlib/utils/link.h												*/
/*																				*/
/* Description:	Genix Foundation Library										*/
/*				Linkage Support													*/
/*																				*/
/* COPYRIGHT (C) Genix InfoComm 2006											*/
/* COPYRIGHT (C) Genitek  2010.05.01											*/
/*																				*/
/* Date			Modification									Name			*/
/* ----			------------									----			*/
/* 2007-04-20	Created											Jake			*/
/*																				*/
/********************************************************************************/
#ifndef _GxLIB_DLINK_H_
#define _GxLIB_DLINK_H_


#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------- */


/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */
typedef struct dlink_s					dlink_t;
typedef dlink_t							*dlink_list_t;
typedef int								(*dlink_comparator)(void *x, void *y);
struct dlink_s
{
	dlink_t					*next;
	dlink_t					*prev;
};


/* variables ------------------------------------------------------------------ */


/* macros --------------------------------------------------------------------- */
#define dlink_foreach(elem, list)												\
	for(elem = (typeof(elem))(list) ;											\
		elem != NULL ;															\
		elem = (typeof(elem))((elem)->dlink.next))

#define dlink_foreach_safe(elem, temp, list)									\
	for(elem = (typeof(elem))(list),											\
		temp = (typeof(temp))((elem) ? ((elem)->dlink.next) : NULL) ;		\
		elem != NULL ;															\
		elem = (typeof(elem))(temp),											\
		temp = (typeof(temp))((elem) ? ((elem)->dlink.next) : NULL) )

#define dlink_append(list, elem)				_dlink_append(&(list), &(elem)->dlink)
#define dlink_prepend(list, elem)				_dlink_prepend(&(list), &(elem)->dlink)
#define dlink_append_list(list1, list2)			_dlink_append_list(&(list1), list2)
#define dlink_prepend_list(list1, list2)		_dlink_prepend_list(&(list1), list2)
#define dlink_insert_list(list1, list2, elem)	_dlink_insert_list(&(list1), list2, &(elem)->dlink)

#define dlink_insert_before(ref, elem)			_dlink_insert_before(&(ref)->dlink, &(elem)->dlink)
#define dlink_insert_after(ref, elem)			_dlink_insert_after(&(ref)->dlink, &(elem)->dlink)
#define dlink_contains(list, elem)				_dlink_contains((list), &(elem)->dlink)
#define dlink_count(list)						_dlink_count(list)
#define dlink_remove(list, elem)				_dlink_remove(&(list), &(elem)->dlink)
#define dlink_sort(list, compare)				_dlink_sort(&(list), compare)

#define dlink_prev_of(elem)				((typeof(elem))((elem) ? (elem)->dlink.prev : NULL))
#define dlink_next_of(elem)				((typeof(elem))((elem) ? (elem)->dlink.next : NULL))
#define dlink_last_of(list)				(void *)((list) ? ((list)->prev):NULL)
#define dlink_of(elem)					((elem) ? &(elem)->dlink : NULL)
#define dlink_first_of(list)				(void *)((list) ? ((list)->next):NULL)


/* functions ------------------------------------------------------------------ */
extern void _dlink_append(dlink_list_t *list, dlink_t *link);
extern void _dlink_prepend(dlink_list_t *list, dlink_t *link);
extern void _dlink_append_list(dlink_list_t *list1, dlink_list_t list2);
extern void _dlink_prepend_list(dlink_list_t *list1, dlink_list_t list2);
extern void _dlink_insert_list(dlink_list_t *list1, dlink_list_t list2, dlink_t *link);
extern void _dlink_insert_before(dlink_t *ref, dlink_t *link);
extern void _dlink_insert_after(dlink_t *ref, dlink_t *link);
extern int _dlink_contains(dlink_list_t list, dlink_t *link);
extern int _dlink_count(dlink_list_t list);
extern void _dlink_remove(dlink_t **list, dlink_t *link);
extern void _dlink_sort(dlink_list_t *list, dlink_comparator compare);


#ifdef __cplusplus
}
#endif
#endif /* _GxLIB_DLINK_H_ */
/* end of file ---------------------------------------------------------------- */
