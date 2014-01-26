
/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my_sdl.h"
#include "slink.h"
#include "th.h"
#include "ui.control.h"
#include "q.h"

#define d_print(...)  dprint(__VA_ARGS__)

typedef struct
{
	unsigned				nospace		: 1;
	unsigned				reserved	: 7;
	task_t					*task;
	char name[20];

} live_instance_t;

static live_instance_t					live_instance;

static int live_control_start(ui_control_t *control);
static int live_control_stop(ui_control_t *control);
static int live_control_ioctl(ui_control_t *control, int type, void *data);
static int live_control_task(void *cookie);


static ui_control_t						live_control =
										{
											.name		= "live11.control",
											.priority	= 1,
											.start		= live_control_start,
											.stop		= live_control_stop,
											.ioctl		= live_control_ioctl,
											.instance	= &live_instance,
											.interval	= 100,	/* ms	*/
											.lifetime	= 0,	/* sec	*/
										};


int live11_control_init(void)
{
	ui_control_t			*control	= &live_control;
	print("%s",__FUNCTION__);

	ui_control_register(control);

	return 0;
}

static int live_control_start(ui_control_t *control)
{
	live_instance_t			*live		= control->instance;
	strcpy(live->name,"live1_control_task");
	live->task=task_create (live_control_task,(void *)control,TASK_STACK_SIZE,TASK_PRIORITY,live->name,0);
	return(0);
}
static int live_control_stop(ui_control_t *control)
{
	live_instance_t			*live	= control->instance;

	if(live->task)
	{
		task_wait(live->task, 1, TIMEOUT_INFINITY);
		task_delete(live->task);
		live->task		= NULL;
		live->nospace	= false;
	}
	return(0);
}

static int live_control_ioctl(ui_control_t *control, int type, void *data)
{
	live_instance_t			*live	= control->instance;
	int wj_test=0x11;

	switch(type)
	{
		case 1:		/* live get duration */
					if(data)
					{
						*(U32*)data = wj_test;
						return(0);
					}
					break;
					
	}
	return(1);
}

static int live_control_task(void *cookie)
{
	
	ui_control_t			*control	= cookie;
	
	osclock_t				timeout		= time_plus(time_now(), control->interval);
	
	char isLoop = 1;
	ui_message_t *m;

	while(isLoop)
	{
		
		SDL_Delay(20);
		//print("Live key?");	

		m=(ui_message_t *)ui_message_receive_timeout(control,&timeout);
		if(m)
		{
			//print("Live key=0x%x",m->key);	
			switch(m->key)
			{
				case SDLK_ESCAPE:
					print(" %s:ESCAPE",control->name);
					isLoop=0;
					break;
				case SDLK_1:
					print(" %s:1",control->name);
					break;
				case SDLK_2:
					
					print(" %s:2",control->name);
					break;
				case SDLK_3:
					
					print(" %s:3",control->name);
					break;
				case SDLK_4:
					print(" %s:4",control->name);
					break;
					
				case SDLK_UP:
					print(" %s:UP",control->name);
					break;
				case SDLK_DOWN:
					print(" %s:DOWN",control->name);
 					break;
				case SDLK_LEFT:
					print(" %s:LEFT",control->name);
					break;
				case SDLK_RIGHT:
					print(" %s:RIGHT",control->name);
					break;
				case SDLK_a:
				case SDLK_w:
				case SDLK_e:
				case SDLK_r:
				
					print(" %s:AWER",control->name);
					break;
				default :
					print(" %s:ETC[0x%x]",control->name,m->key);

					break;
					
					
			}
			
			if(ui_message_release(m)!=0) print("q_release fail");
		}
		else
		{
			
	 	//	print("N");
		}	
	}
	
	ui_control_release(control);
	print("Exit %s ",control->name);

	//sdl_key_stop();
	
	//sdl_stop();

 	return;
}


