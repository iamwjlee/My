
/* includes ------------------------------------------------------------------- */

#include "my_sdl.h"
#include "event.h"

#define d_print(...) printf(__VA_ARGS__)
/*

typedef void (*event_callback_func_t)(	event_driver_t *event,
										int id,
										void *data,
										void *cookie);
event_driver_t		*tuner_event;
tuner_event 	= event_driver_create(TUNER_EVENT_COUNT);

event_notify(tuner_event, TUNER_EVENT_CHANNEL_CHANGED, tp);
int tp_view_init(void)
{ ...
	event_subscribe(tuner_event, TUNER_EVENT_CHANNEL_CHANGED, tp_changed_callback, &tp_instance);
}
*/




/* global functions ----------------------------------------------------------- */
event_driver_t *event_open(const char *name)
{
	event_driver_t			*event = calloc(1, sizeof(event_driver_t) );

	if(event)
	{
		//event->lock		= mutex_create_fifo();
		strcpy(event->name,"tuner");
		return(event);

	}
	return NULL;
}

int event_init(char *name, event_driver_t **e)
{
	event_driver_t			*event = calloc(1, sizeof(event_driver_t) );

	if(event)
	{

		//event->lock		= mutex_create_fifo();
		strcpy(event->name,name);
		*e=event;
		return 0;
	}
	return 1;
}

int  event_subscribe(event_driver_t *event, int id, event_callback_func_t callback, void *cookie)
{
	if(event &&1)
	{
		event->subscriber=calloc(1, sizeof(event_subscriber_t));
		if(event->subscriber)
		{

			event->subscriber->cookie		= cookie;
			event->subscriber->id=id;
			event->subscriber->callback	= callback;

			//mutex_lock(event->lock);
			#if 0
			slink_foreach(exist, item)
				if((exist->callback == callback) && (exist->cookie == cookie)) 	break;
			if(exist)
			{
				free(subscriber);
				//mutex_release(event->lock);
				d_print(" exit-------------\n");
				return(false);
			}
			#endif
		
			slink_add_front(event->list, event->subscriber);
			//mutex_release(event->lock);
			return(0);
		}
	}
	return(1);
}

void event_unsubscribe(event_driver_t *event, int id, event_callback_func_t callback)
{
	if(event &&1)
	{
		//event_subscriber_t		*safe;

		//slink_foreach_safe(event->subscriber, safe, event->list)
		slink_foreach(event->subscriber, event->list)
			if(event->subscriber->callback == callback && event->subscriber->id == id)
			{
				slink_remove(event->list, event->subscriber);
				free(event->subscriber);
				//break;
			}
	}
}

void event_notify(event_driver_t *event, int id, void *data)
{
	if(event && 1 )
	{
		//event_subscriber_t		*safe;

		
		//slink_foreach_safe(subscriber, safe, event->list)
		
		slink_foreach(event->subscriber,  event->list)
		//slink_foreach_safe(event->subscriber, safe, event->list)
			if(event->subscriber->callback && event->subscriber->id==id)
			{
				event->subscriber->callback(event, id, data, event->subscriber->cookie);
			}	
	}
}

//--------------------------------------------------
typedef enum
{
	EVENT_0,
	EVENT_1,
	EVENT_2,
	EVENT_3,
	EVENT_4,
	EVENT_COUNT
} tuner_event_t;

static void test_callback(event_driver_t *event, int id, void *data, void *cookie)
{
	char 	*instance	= cookie;
	char		*tp			= data;

	//if(id == TUNER_EVENT_CHANNEL_CHANGED)
	{
		//set_tp_text(instance, tp, 0);
		strcpy(instance,data);
		d_print("id[%d] tp_changed_callback [data=%s] [instance=%s] \n",id,tp,instance);
	}
}


void event_test(void)
{
	char test_instance[20];	
	char data[20];
	//int err;
	//event_subscriber_t *sub;
	event_driver_t		*tuner_event;
	//tuner_event 	= event_driver_create(1);
	d_print("event_test\n");
	event_init("mytuner",&tuner_event);
	//d_print("tuner_event:0x%x\n",tuner_event);

	event_subscribe(tuner_event, EVENT_0, test_callback, test_instance);
	//d_print("event_subscribe err:%d\n",err);

	event_subscribe(tuner_event, EVENT_1, test_callback, test_instance);
	//d_print("event_subscribe err:%d\n",err);

	slink_foreach(tuner_event->subscriber, tuner_event->list)
	{
		d_print("[%s][0x%x] subscriber->id=%d	\n",tuner_event->name,(unsigned int)tuner_event->subscriber,tuner_event->subscriber->id);
	} 


	
	strcpy(data,"first event");
	event_notify(tuner_event, EVENT_0, data);
	
	event_unsubscribe(tuner_event, EVENT_0,test_callback);
	
	strcpy(data,"2nd event");
	event_notify(tuner_event, EVENT_0, data);
	
	strcpy(data,"3rd event");
	event_notify(tuner_event, EVENT_1, data);
	
	slink_foreach(tuner_event->subscriber, tuner_event->list)
	{
		d_print("[%s][0x%x] subscriber->id=%d	\n",tuner_event->name,(unsigned int)tuner_event->subscriber,tuner_event->subscriber->id);
	} 


}

/* local functions ------------------------------------------------------------ */


/* end of file ---------------------------------------------------------------- */
