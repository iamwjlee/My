#include "common.h"
#include <pthread.h>
//#include <signal.h>
//#include <sys/types.h>
#include <unistd.h> //sleep

#include "sys.h"
int momo=0;

int m_task_create(void *(*function)(void *),void *param,int *task_id)
{
	pthread_t t;
	pthread_create(&t,NULL,function,param);
	//pthread_join(t,&s);
	//print(" thread stop? %s ",(char *)s);
	print("t = 0x%x",(unsigned int)t);
	*task_id = t;
	return 0;

}

int m_task_delete(int task_id)
{	
	void *s;
	pthread_join(task_id,&s);
	print("pthread_join okay[%s]",(char *)s);
	return 0;
}
//

/*
	let's make simple task as disp_t

*/

typedef struct disp_s
{
	int tid;
	int running;
	char title[32];
	struct disp_s *next;
}disp_t;

static disp_t *list=NULL;

int show_disp_task(void)
{
	disp_t *p;
	p=list;
	while(p)
	{
		print(" task title[%s]",p->title);
		p=p->next;

	}
	return 0; 

}

void *disp01(void *arg)
{
	disp_t *p=(disp_t *)arg;
	while(p->running)
	{
		print("disp:%s",p->title);
		sleep(2);

	}
	return (void *)0;
}

int m_task_test(void)
{
	disp_t *p;
	disp_t *p1;
	disp_t *p0;
	disp_t *prev;
	p= (disp_t *)malloc(sizeof(disp_t));
	memset(p,0,sizeof(disp_t));
	p->running =1;
	p->next=NULL;
	strcpy(p->title,"01");
		
	m_task_create(disp01,(void *)p,&p->tid);

	if(list) p->next=list;
	list=p;

	p1= (disp_t *)malloc(sizeof(disp_t));
	memset(p1,0,sizeof(disp_t));
	p1->running =1;
	p1->next=NULL;
	strcpy(p1->title,"02");
		
	m_task_create(disp01,(void *)p1,&p1->tid);

	if(list) p1->next=list;
	list=p1;

	{
		disp_t *p;
		p=list;
		while(p)
		{
			print(" %s",p->title);
			p=p->next;
		}

	}

	print("p->tid %x",p->tid);
	sleep(5);
	p->running=0;
	m_task_delete(p->tid);
	

	p0=prev=list;
	while(p0)
	{
		if(p0->tid==p->tid) break;
		prev=list;
		p0=p0->next;
	}
	if(p0)
	{
		if(p0==list) list = p0->next;
		else prev->next = p0->next;

		free(p0);

	}
	print(" delete one ");
	p0=list;
	while(p0)
	{
		print(" %s",p0->title);
		p0=p0->next;
	}

	return 0;
}




//------------------------------------------

void *functionxx(void *p)
{
	while(1)
	{
	print(" child ");
	sleep(2);
	}

}

int thread_test(void)
{
	//void *s;
	pthread_t t;
	int a;
	pthread_create(&t,NULL,functionxx,(void *)&a);
	while(0)
	{
		print("parent");
		sleep(1);

	}
	//pthread_join(t,&s);
	//print(" thread stop? %s ",(char *)s);
	return 0;

}
//--------------------------------------------
