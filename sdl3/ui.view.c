#include "my_sdl.h"
#include "slink.h"
#include "widget.h"
#include "q.h"
#include "ui.control.h"
#include "ui.h"
#include "th.h"


#define d_print(...)  dprint(__VA_ARGS__)

/* includes ------------------------------------------------------------------- */


/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */


/* macros --------------------------------------------------------------------- */


/* local function prototypes -------------------------------------------------- */
static void	ui_view_task(void *cookie);
static int	try_show(ui_view_t *request);
//static void display_event_callback(event_driver_t *event, event_id_t event_id, void *data, void *cookie);
static int rectangle_overlapped(gfx_rectangle_t *rect1, gfx_rectangle_t *rect2);


/* local variables ------------------------------------------------------------ */
static struct
{
	BOOL					granted;
	gfx_rectangle_t			used;
	slink_list_t			list;
	//semaphore_t				*stop;
	task_t					*task;
} ui_view;


/* global variables ----------------------------------------------------------- */
//mutex_t									*ui_view_lock;


/* global functions ----------------------------------------------------------- */
int ui_view_init(void)
{
	
	//print("%s\n",__FUNCTION__);
	//task_create (&ui_view.task ,ui_view_task,(void *)null,TASK_STACK_SIZE,TASK_PRIORITY,"ui.view",0);
	return(0);
}

int ui_view_register(ui_view_t *view)
{
	view->lifetime *= time_ticks_per_sec();

	slink_add_front(ui_view.list, view);
	
	slink_foreach(view, ui_view.list)
	{
		d_print("ui_view_register %s   p:%d \n",view->name,view->priority);

	}
	return(0);
}

int ui_view_unregister(ui_view_t *view)
{
	slink_remove(ui_view.list, view);
	return(0);
}

ui_view_t *ui_view_search(const char *name)
{
	ui_view_t				*view;

	if(name)
	{
		slink_foreach(view, ui_view.list)
			if(!strcmp(view->name, (char*)name))
			{
				return(view);
			}
	}
	return(null);
}

int ui_view_show(ui_view_t *request)
{
	ui_view_t				*view;
	print47("%s---start[%s] --->",__FUNCTION__,request->name);
	if(request)
	{
		slink_foreach(view, ui_view.list)
			if((view == request) || !strcmp(view->name, (char*)request))
			{
				view->active = true;
				view->paused = false;
				if(view->visible)   // when key down in the root menu  , menu_view_show in the menu_run
				{
					view->show(view);
					view->expire = view->lifetime ? time_plus(time_now(), view->lifetime) : 0;
					//VIEW_UNLOCK();
					
					print47("%s ---visible[%d]---end     ! Review this case !",__FUNCTION__,view->visible);
					
					print47("%s ---end[%s] ",__FUNCTION__,request->name);
					return(0);
				}
				else if(try_show(view))  //volume
				{
					//VIEW_UNLOCK();
					return(-1);
				}
				
				print47("%s ---end[%s] <---",__FUNCTION__,request->name);
				//VIEW_UNLOCK();
				return(0);
			}
		//VIEW_UNLOCK();
	}
	return(-1);
}

int ui_view_hide(ui_view_t *request)
{
	ui_view_t				*view;

	
	if(request)
	{
		slink_foreach(view, ui_view.list)
			if((view == request) || !strcmp(view->name, (char*)request))
			{
				print3745("ui_view_hide :  %s",view->name);	
				view->active	= false;
				view->protect	= 0;
				if(view->visible)
				{
					view->visible = false;
					view->hide(view);
					print3745("ui_view_hide() HIDED(%s)", view->name);
				}
				else
				{
					err("ui_view_hide: view->visible=0");
				}	
				return(0);
			}
	}
	return(-1);
}

int ui_view_extends(ui_view_t *request, int seconds)
{
	ui_view_t				*view;

	if(request)
	{
		//VIEW_LOCK();
		slink_foreach(view, ui_view.list)
			if((view == request) || !strcmp(view->name, (char*)request))
			{
				if(view->visible)
				{
				//	if(seconds)
				//		view->expire = time_plus(time_now(), time_ticks_per_sec() * seconds);
				//	else	view->expire = view->lifetime ? time_plus(time_now(), view->lifetime) : 0;
					return(0);
				}
				break;
			}
	}
	return(-1);
}

int ui_view_update(ui_view_t *request)  // need ?
{
	ui_view_t				*view;

	if(request)
	{
		//VIEW_LOCK();
		slink_foreach(view, ui_view.list)
			if((view == request) || !strcmp(view->name, (char*)request))
			{
				if(view->visible)
				{
					print("view_update(%s)\n", view->name);
					 view->update(view);
					//VIEW_UNLOCK();
					return(0);
				}
				break;
			}
		//VIEW_UNLOCK();
	}
	return(-1);
}

int ui_view_pause(ui_view_t *request)
{
	ui_view_t				*view;

	if(request)
	{
		//VIEW_LOCK();
		slink_foreach(view, ui_view.list)
			if((view == request) || !strcmp(view->name, (char*)request))
			{
				if(view->paused || !view->pause || !view->pause(view))
				{
					view->paused = true;
					//VIEW_UNLOCK();
					return(0);
				}
				break;
			}
		//VIEW_UNLOCK();
	}
	return(-1);
}

int ui_view_resume(ui_view_t *request)
{
	ui_view_t				*view;

	if(request)
	{
	//	VIEW_LOCK();
		slink_foreach(view, ui_view.list)
			if((view == request) || !strcmp(view->name, (char*)request))
			{
				if(!view->resume || !view->resume(view))
				{
					view->paused = false;
					//VIEW_UNLOCK();
					return(0);
				}
				break;
			}
		//VIEW_UNLOCK();
	}
	return(-1);
}

int ui_view_ioctl(ui_view_t *request, int type, void *data)
{
	int						result	= -1;
	ui_view_t				*view;

	if(request)
	{
	//	VIEW_LOCK();
		slink_foreach(view, ui_view.list)
			if((view == request) || !strcmp(view->name, (char*)request))
			{
				if(view->ioctl)
					result = view->ioctl(view, type, data);
				break;
			}
		//VIEW_UNLOCK();
	}
	return(result);
}

int ui_view_lifetime(ui_view_t *request, int second)
{
	int						result	= -1;
	ui_view_t				*view;

	if(request)
	{
		//VIEW_LOCK();
		slink_foreach(view, ui_view.list)
			if((view == request) || !strcmp(view->name, (char*)request))
			{
				////view->lifetime = time_ticks_per_sec() * second;
				result = 0;
				break;
			}
		//VIEW_UNLOCK();
	}
	return(result);
}

int is_ui_view(char *name)  //for biss
{
	ui_view_t				*view;

	slink_foreach(view, ui_view.list)
	{
		if(view->visible) {
				print("view->name[%s]\n",view->name);
			if(!strcmp(name,view->name)) return 1;
		}	

	}	
	return 0;
}	


/* local functions ------------------------------------------------------------ */

static void ui_view_task(void *cookie)
{
	//osclock_t				interval;	//= time_ticks_per_sec() / 16;
	//osclock_t				timeout; //		= time_plus(time_now(), interval);
	ui_view_t				*view;


	while(1) //(semaphore_wait_timeout(ui_view.stop, &timeout))
	{
		//timeout = time_plus(time_now(), interval);
		usleep(200000);

		//VIEW_LOCK();
		slink_foreach(view, ui_view.list)
			if(view->visible)
			{
				if(!view->active || (view->expire && time_after(time_now(), view->expire)))
					
				//if(!view->active || 1)
				{
					view->expire	= 0;
					view->active	= false;
					view->visible	= false;
					//flip_start();
					view->hide(view);  //live view
					//flip_end(false);
					print("time's up!   view->hide in the view task(%s)\n", view->name);
				}
			}

		if(ui_view.granted)
		{
			slink_foreach(view, ui_view.list)
				if(view->visible)
				{
					if(	!view->paused &&
						view->update &&
						view->update_time &&
						time_after(time_now(), view->update_time)
					)
					{
						view->update_time = 0;
						
						//print("ui_view_task[%s]\n",view->name);
						view->update(view);  //wallpaper , channel info banner(live.view), hourglass,disk.view in the usb menu, no signal banner
					}
				}
				else if(view->active)
				{
					err("try_show in view task[%s]",view->name);
					try_show(view);  //view->show(view)
				}
		}
		//VIEW_UNLOCK();
	}
}

static int try_show(ui_view_t *request)
{
	ui_view_t				*exist;
	int						error;

	print("-->try_show[%s]\n",request->name);
	
	if(rectangle_overlapped(&request->area, &ui_view.used))
	{
		
		print("try_show() exit0 [%d] \n", request->priority);
		return(-1);
	}	

	slink_foreach(exist, ui_view.list)
		if((exist != request) && exist->visible && rectangle_overlapped(&exist->area, &request->area))
		{
			if(exist->priority > request->priority)
			{
				
				print("try_show() exit1 [%d > %d] \n", exist->priority,request->priority);
				return(-1);
			}
			#if 0
			else if(exist->priority == request->priority)
			{
			//	if(exist->protect && !time_after(time_now(), exist->protect))
					
				if(exist->protect && 1)
				{
					
					print("try_show() exit2 \n");
					return(-1);
				}	
				else if(request->protect)
				{
					
					print("try_show() exit3 \n");
					return(-1);
				}	
			}
			#endif
		}

//	flip_start();
#if 0
	slink_foreach(exist, ui_view.list)
		if((exist != request) && exist->visible && rectangle_overlapped(&exist->area, &request->area))
		{
			exist->visible = false;
			exist->hide(exist);
			print("try_show() HIDE(%s)\n", exist->name);
		}
#endif		
	error = request->show(request); //
	//flip_end(false);

	if(!error)
	{
		request->visible = true;  //here
		request->expire = request->lifetime ? time_plus(time_now(), request->lifetime) : 0;  //here
		print("<--try_show[%s] SHOWED\n\n", request->name);
	}
	return(error);
}

static int rectangle_overlapped(gfx_rectangle_t *rect1, gfx_rectangle_t *rect2)
{
	int						x_clipped = false;
	int						y_clipped = false;

	if(rect1->w && rect2->w)
		x_clipped = ((rect2->x < (rect1->x + rect1->w)) && (rect1->x < (rect2->x + rect2->w)));

	if(rect1->h && rect2->h)
		y_clipped = ((rect2->y < (rect1->y + rect1->h)) && (rect1->y < (rect2->y + rect2->h)));

	return(x_clipped && y_clipped);
}


/* end of file ---------------------------------------------------------------- */
