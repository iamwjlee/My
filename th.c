#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my_sdl.h"
#include "slink.h"
#include "th.h"

#define d_print(...)  dprint(__VA_ARGS__)

struct task_list_s
{
	slink_t slink;
	task_t *task;
	char name[32];
};
typedef struct task_list_s task_list_t;

static slink_t *TaskList;

task_t *task_create (int (*function)(void*),void* param,int stack_size,int priority,const char* name,task_flags_t flags)
{
	task_list_t *list;		
	task_t *task=NULL;


	
	task = SDL_CreateThread( function,	(void *)param);
	if(task!=NULL)
	{
		list=calloc(1,sizeof(task_list_t));
		list->task=task;
		strcpy(list->name,name);
		slink_add_back(TaskList,list);
	}
	
	return task;

	
}


int task_wait(task_t *task, int ntasks, unsigned long *timeout)
{
	int status;
	task_list_t *list;
	char name[32];
	int threadReturnValue;
	memset(name,0,sizeof(char)*8);
	slink_foreach(list, TaskList)
	{
		//d_print("\t\t\t m[%x] [%x] [%x]",list->name,list->task,*task,task);
		if(list->task==task)
		{
			strcpy(name,list->name);
			//d_print("\t\t\t name=%s",list->name);
			break;
		}
	}	
	
	d_print("\t\t\t remove list=%s",list->name);
	slink_remove(TaskList, list);
	d_print("\t\t\t free list=%s",list->name);
	free(list);

	SDL_WaitThread( task, &threadReturnValue);
	
	if(name)
		d_print("\t\t\t task_wait  [%s][%x] ",name,threadReturnValue);
	return 0;

}

int task_delete(task_t *task)
{
	
	//SDL_KillThread( task );
	//print("\t\t\t task_deleted\n");
	return 0;

}


//---------------------------------------------------------------


typedef struct
{
	int g_on;
	int cnt;
	task_t *task;
}my_first_t;

my_first_t *my_thread;
int TestThread( void *data )
{
		my_first_t *my=(my_first_t *)data;
        my->cnt=10;
		while(my->g_on)
        {
                d_print( "\nThread counter: %d", my->cnt++);
                SDL_Delay(20);
        }
		
        return 0;
}

void th_test0()
{
	my_thread=malloc(sizeof(my_first_t));
	my_thread->g_on=1;
	my_thread->task = SDL_CreateThread( TestThread,  (void *)my_thread);
	SDL_Delay(2000);
	my_thread->g_on=0;
	SDL_WaitThread( my_thread->task, NULL);
	d_print("\nMy First thread_test0 end");
	
}




/* let's make basic mycounting thread object  */

struct mycounting_s
{
	task_t *task;
	int counting;
	char name[20];
	int running;
	int (*set)(void *, int v);
};
typedef struct mycounting_s mycounting_t;


int  counting(void *data)
{
	int i=0;
	mycounting_t *p=(mycounting_t *)data;
	while(p->running)
	{
		 d_print("%s[0x%x] : %d [%d]",p->name,(unsigned int )p,p->counting,p->running);
		p->counting++;
		SDL_Delay(500);
	}
	return 0;
}

void th_test()
{
	mycounting_t *my1;
	mycounting_t *my2;
	
	mycounting_t *p;
	d_print("test");

/* make instance my1 */
	my1= (mycounting_t *)malloc(sizeof(mycounting_t));
	strcpy(my1->name,"home");
	my1->counting=10;
	my1->running=1;
	 my1->task = task_create (counting,(void *)my1,TASK_STACK_SIZE,TASK_PRIORITY,my1->name,0);

/* make nstance my2 */
	my2=(mycounting_t *)malloc(sizeof(mycounting_t));

	strcpy(my2->name,"office");
	my2->counting=100;
	my2->running=1;
	my2->task=task_create (counting,(void *)my2,TASK_STACK_SIZE,TASK_PRIORITY,my2->name,0);

	SDL_Delay(1000*3);
	
	my1->running=0;
	task_wait(my1->task, 1, TIMEOUT_INFINITY);
	task_delete(my1->task);
	SDL_Delay(1000*2);

	
	my2->running=0;
	task_wait(my2->task, 1, TIMEOUT_INFINITY);
	task_delete(my2->task);


}


//
#if 0
int  get_key(void *data)
{
	
}
#endif


