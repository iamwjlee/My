
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my_sdl.h"
#include "slink.h"
#include "th.h"
#include "q.h"
#include "ui.control.h"

#define d_print(...)  dprint(__VA_ARGS__)




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
					d_print("w:%d. h:%d",event.resize.w,event.resize.h);
					}
							break;
				case SDL_QUIT:
					
					msg=ui_message_claim(TIMEOUT_IMMEDIATE);
					if(msg)
					{
						//msg->key=event.key.keysym.sym;
						msg->type=CONTROL_SDL_QUIT;
						ui_message_send((void *)msg);
					}
					
					d_print("window close");
					break;
					

			}
		} 		

	}
	return 0;

}


int sdl_key_start(void)
{
	sdl_key.running=1;
	strcpy(sdl_key.name,"keyboard");
	
	d_print("%s",__FUNCTION__);
	
	sdl_key.task = task_create (get_sdl_key,(void *)&sdl_key,TASK_STACK_SIZE,TASK_PRIORITY,sdl_key.name,0);
	return 0;

}

int sdl_key_stop(void)
{
	sdl_key.running=0;
	
	task_wait(sdl_key.task, 1, TIMEOUT_INFINITY);
	task_delete(sdl_key.task);
	//print("[%s] task deleted \n",sdl_key.name);

	return 0;
}



