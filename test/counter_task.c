#include "common.h"
#include "sys.h"
#include "task.h"

/*

	make object 
	which is simply counting 
	which is able to be called multi instances by task
	


*/



typedef struct cnt_s
{

	int tid; //tast_id
	char name[16];
	int running;
	int value;
	struct cnt_s *next;
}cnt_t;


static cnt_t *list=NULL;

int show_my_counting(void)
{
	cnt_t *p;
	p=list;
	while(p)
	{
		print("my_counting[%s]",p->name);
		p=p->next;

	}

	return 0;
}

void *my_counting(void *arg)
{
	cnt_t *p=(cnt_t *)arg;
	while(p->running)
	{
		
		print("counting[%d]",p->value);
		p->value++;
		sleep(2);


	}
	return (void *)0;

}
int my_counting_open(char* name,int value)
{
	cnt_t *p;
	p=(cnt_t *)mem_alloc(1,sizeof(cnt_t));
	strcpy(p->name,name);
	p->running = 1;
	p->value = value;
	p->next= NULL;
	m_task_create(my_counting,(void *)p,&p->tid);

	/* Attached obj to the list */	
	if(list) p->next=list;
	list=p;	

	return 0;

}

int my_counting_close(char *name)
{
	cnt_t *p0; //previous 
	cnt_t *p=list;
	if(list==NULL) return 1;

	while(p)
	{
		if(!strcmp(p->name,name)) break;
		p0=p;
		p=p->next;
	}
	if(p)
	{
		/* Detached obj from the list */
		if(p==list) list=p->next;
		else p0->next=p->next;
		/* Delete task */
		p->running=0;
		m_task_delete(p->tid);	
		/* Deallocate obj */
		mem_dealloc((u32)p);
	}


	return 0;
}


int my_counter_task_test(void)
{

	my_counting_open("wj", 1);
	my_counting_open("hj",100);
	my_counting_open("js",200);
	show_my_counting();
	
	sleep(5);
	my_counting_close("wj");
	sleep(5);
	show_my_counting();

	return 0;


}
