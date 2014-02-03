#ifndef _EVENT_H
#define _EVENT_H

/* includes ------------------------------------------------------------------- */
//nclude "my_sdl
#include "slink.h"

#ifdef __cplusplus
extern "C" {
#endif

#if 0
typedef struct
{
	//slink_list_t			subscribers;
	slink_t *subscribers;
} event_item_t;
#endif

typedef struct event_driver_s			event_driver_t;

typedef void (*event_callback_func_t)(	event_driver_t *event,int id,	void *data,void *cookie);

typedef struct
{
	slink_t	slink; //implicit,unconditional
	void	*cookie;
	int id;
	event_callback_func_t	callback;
	
} event_subscriber_t;


struct event_driver_s
{
	//mutex_t					*lock;
	//int					count;
	char name[20];
	event_subscriber_t *subscriber;
	slink_t *list;
};





/* functions ------------------------------------------------------------------ */
extern event_driver_t *event_driver_create(int count);
extern int  event_subscribe(event_driver_t *event, int id, event_callback_func_t callback, void *cookie);
extern void event_unsubscribe(event_driver_t *event, int id, event_callback_func_t callback);

extern void event_notify(event_driver_t *event, int id, void *data);
extern void event_test(void);


#ifdef __cplusplus
}
#endif
#endif 
/* end of file ---------------------------------------------------------------- */
