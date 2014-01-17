
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my_sdl.h"
#include "slink.h"
#include "th.h"
#include "ui.control.h"
#include "q.h"

typedef struct
{
	//slink_list_t			list;
	slink_list_t			focused;
	task_t					*task;
	char  name[20];
	int running;
} root_instance_t;
static root_instance_t					root_instance;

static ui_control_t						ui_control =
										{
											.name		= "ui.control",
											.instance	= &root_instance,
											.active		= true,
											.running	= true,
											.interval	= 100,		/* ms				*/
											.lifetime	= 65536,	/* sec: 18.2 hours	*/
										};

static slink_list_t						control_list;

msg_queue_t *ui_q;

static int ui_control_task(void *cookie);

int ui_control_register(ui_control_t *control)
{
	//UI_TRACE_T("ui_control_register(%s)", control->name);
	//control->awake		= semaphore_create_fifo_p(ui_partition, 0);
	///control->interval	= msec_to_clocks(control->interval);
	//control->lifetime	= time_ticks_per_sec() * control->lifetime;
	//if(!control->lifetime) 		control->lifetime = time_ticks_per_sec() * 60;

	//API_LOCK();
	slink_add_front(control_list, control);
	//API_UNLOCK();
	return(0);
}

static void trace_focused_list(slink_list_t list)
{
	char					buffer[256] = "FOCUSED: ";
	char					string[64];
	ui_control_t			*focused;

	slink_foreach(focused, list)
	{
		sprintf(string, "%s(%02X)>", focused->name, focused->priority);
		strcat(buffer, string);
	}
	print("%s\n", buffer);
}

ui_control_t *ui_control_focused(void)
{
	root_instance_t			*root	= &root_instance;

	return((ui_control_t*)root->focused);
}

int ui_control_delete(void)
{
	ui_control_t			*control	= &ui_control;
	root_instance_t			*root		= control->instance;
	root->running=0;
	task_wait(root->task, 1, TIMEOUT_INFINITY);
	task_delete(root->task);
	print("[%s] task deleted \n",root->name);

}

int ui_control_init(void)
{
	ui_control_t			*control	= &ui_control;
	root_instance_t			*root		= control->instance;
	print("%s\n",__FUNCTION__);

	//api_lock			= mutex_create_fifo_p(ui_partition);
	//ui_queue			= ui_queue_create_p(ui_partition, MAX_MESSAGE_COUNT, sizeof(ui_message_t));
	//repeat_start_delay	= time_ticks_per_sec() / 2;   //

	//control->awake		= semaphore_create_fifo_p(ui_partition, 0);
	//control->interval	= msec_to_clocks(control->interval);
	//control->lifetime	= time_ticks_per_sec() * control->lifetime;
	//if(!control->lifetime) 		control->lifetime = time_ticks_per_sec() * 60;
	root->running=1;
	strcpy(root->name,"ui_control_task");
	slink_add_front(root->focused, control);
	//ui_shell_init();
	root->task=task_create (ui_control_task,(void *)control,TASK_STACK_SIZE,TASK_PRIORITY,root->name,0);

	//root->task		= task_create_p(ui_partition, ui_control_task, control,
	//								ui_partition, TASK_STACK_SIZE, TASK_PRIORITY, "ui.control",
	//								task_flags_suspended |
	//								task_flags_no_min_stack_size);
	return(0);
}
int ui_control_start(ui_control_t *request, int *msg)
{
	root_instance_t			*root	= &root_instance;
	ui_control_t			*control;

	//errno = EINVAL;
	if(request)
	{
		//errno = ENODEV;
		//API_LOCK();
		slink_foreach(control, control_list)
			if((control == request) || !strcmp(control->name, (char*)request))
			{
				ui_control_t			*focused = slink_first(root->focused);

				print("ui_control_start(%s)\n", control->name);
				if(!control->start(control))
				{
					//ui_event_params_t		params = { .now = focused, .next = control };

					focused->paused = true;
					control->active = control->running = true;
					slink_remove(control_list, control);
					slink_add_front(root->focused, control);
					//trace_focused_list(root->focused);

					//if(msg)	ui_massage_undo_receive(msg);
					//event_notify(ui_event, UI_EVENT_FOCUS_CHANGED, &params);
					print("UI_EVENT_FOCUS_CHANGED[%s]\n",control->name );  // can not see menu osd!
					//ui_control_awake(control);
					//API_UNLOCK();
					return(0);
				}
				//ui_massage_release(msg);
			}
		//API_UNLOCK();
	}
	return(-1);
}

static int ui_control_task(void *cookie)
{
	root_instance_t			*root	= &root_instance;
	//ui_queue_t				*queue	= ui_queue;
	ui_control_t			*control, *safe;
	ui_control_t			*focused;
	int						i;

	//UI_TRACE_T("ui_control_task() STARTED");
	//event_subscribe(front_event, FRONT_EVENT_KEY_PRESS,		key_press_callback,		null);
	//event_subscribe(front_event, FRONT_EVENT_KEY_RELEASE,	key_release_callback,	null);

	while(root->running)
	{
		//osclock_t				timeout	= time_plus(time_now(), ui_control.interval);
		//ui_message_t			*msg	= ui_massage_receive_timeout(&ui_control, &timeout);

		//API_LOCK();
		
		SDL_Delay(10);
		focused = slink_first(root->focused);
		while(!focused->active && focused->running)
		{
			//ui_event_params_t		params	= { .now = focused };

			//task_delay(msec_to_clocks(100));  //20120813

			control = slink_remove_front(root->focused);   //focus out
			slink_add_front(control_list, control);    
			if(control->stop)
				control->stop(control);
			control->running = false;

			trace_focused_list(root->focused);

			#if 0
			focused = slink_first(root->focused);
			//params.next = focused;
			//event_notify(ui_event, UI_EVENT_FOCUS_CHANGED, &params);
			if(focused->active)
			{
				ui_control_awake(focused);
			}
			#endif
		}



		//ui_queue_release(queue, msg);
	}
}

int ui_control_expired(ui_control_t *control)
{
	return(time_after(time_now(), control->expire));
}


int ui_control_release(ui_control_t *control)
{
	control->active = false;
	//ui_control_flush(control);
	//semaphore_signal(ui_control.awake);
	return(0);
}

//*----------------------------------------------------------------


void  show_ui_message_queue(void)
{
	int i;
	msg_t *queue;
	slink_foreach(queue, ui_q->slist)
	{
		print("\t queue[0x%x] queue->msg=%d queue->state=%d \n",(unsigned int)queue,*(int *)queue->msg,queue->state);
	} 
	print("\n");
	queue=ui_q->queue;
	for(i=0;i<ui_q->count;queue++,i++)
	{
		print("\t\t queue[0x%x] queue->msg=%d	queue->state=%d \n",(unsigned int)queue,*(int *)queue->msg,queue->state);
	}

}
ui_message_t *ui_message_claim(osclock_t *timeout)
{
	ui_message_t *m;
	m=(ui_message_t *)q_claim(ui_q);
	return m;
}

//msg_queue_t *ui_message_open(const char *name, int q_size ,int m_size)
//{
//	return (q_open(name, q_size ,m_size));
//}

int ui_message_init(const char *name, int q_size )
{
	
	print("%s\n",__FUNCTION__);
	 ui_q=q_open(name, q_size ,sizeof(ui_message_t));
	 return 0;
 }

int ui_message_delete()
{
	q_delete(ui_q);

}
int ui_message_send(ui_message_t *msg)
{
	return (q_send(ui_q,(void *)msg));

}
ui_message_t *ui_message_receive_timeout(ui_control_t *control,osclock_t *timeout)
{
	
	root_instance_t	*root	= &root_instance;
	ui_message_t		*msg=NULL;
	
	if(root->focused == (void*)control)
		msg=(ui_message_t *)q_receive(ui_q);
	//else print(" .");
	return msg;

}
ui_message_t *ui_message_receive(ui_control_t *control)
{
	
	root_instance_t	*root	= &root_instance;
	ui_message_t		*msg=NULL;
	
	if(root->focused == (void*)control)
		msg=(ui_message_t *)q_receive(ui_q);
	//else print(" .");
	return msg;

}

int ui_message_release(ui_message_t *msg)
{
	return (q_release(ui_q, (void *)msg));
}


//--------------------------------------------------------------------

struct my_key_s
{
	
	task_t					*task;
	char name[20];
	int running;
	//char key;
};
typedef struct my_key_s sdl_key_t;
sdl_key_t sdl_key;

static int  get_sdl_key(void *data)
{
	SDL_Event event;
	sdl_key_t *p=(sdl_key_t *)data;
	ui_message_t *msg;
	while(p->running )
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{

				case SDL_KEYDOWN:
					//switch(event.key.keysym.sym)
					{
						//print("keydown [%x]\n",event.key.keysym.sym);
						msg=ui_message_claim(TIMEOUT_IMMEDIATE);
						if(msg)
						{
							msg->key=event.key.keysym.sym;
							msg->type=CONTROL_KEY_PRESSED;
							ui_message_send((void *)msg);
						}
							
					}
					break;

				case SDL_VIDEORESIZE:
					{
					print("w:%d. h:%d \n",event.resize.w,event.resize.h);
					}
							break;
				case SDL_QUIT:
					print("window close\n");
					break;
					

			}
		} 		

	}

}


int sdl_key_start(void)
{
	sdl_key.running=1;
	strcpy(sdl_key.name,"keyboard");
	
	print("%s\n",__FUNCTION__);
	
	sdl_key.task = task_create (get_sdl_key,(void *)&sdl_key,TASK_STACK_SIZE,TASK_PRIORITY,sdl_key.name,0);

}

int sdl_key_stop(void)
{
	sdl_key.running=0;
	
	task_wait(sdl_key.task, 1, TIMEOUT_INFINITY);
	task_delete(sdl_key.task);
	//print("[%s] task deleted \n",sdl_key.name);


}



