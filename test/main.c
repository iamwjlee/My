
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//#include <signal.h>
//#include <sys/types.h>
#include <unistd.h> //sleep


#include "task.h"
#define print(f,...) printf(f"%s",##__VA_ARGS__,"\r\n")

typedef struct my_mem_s
{
	int type;
	int addr;
	int size;
	struct my_mem_s *next;	

}my_mem_t;

static my_mem_t *mem_list=NULL;


//
void *function00(void *p)
{
	int *arg=(int *)p; 
	while(*arg==1)
	{
	print(" child ");
	sleep(2);
	}
	return 0;
}
//
int *get_mem(int size )
{
	int *p;
	p=malloc(size);
	*p=1;
	return p;
	
}
int get_mem2(int **pp,int size)
{
	
	int *p;
	p=malloc(size);
	*p = 5;
	print("	get_mem2: 0x%08x:%d",(int)p,*p);

	*pp=p;
	return 0;
	

}

int point_test(void)
{
	int m=3;
	int *p=&m;
	int **pp= &p;
	int *p2;
	
	print(" %d",m);
	print(" %x",*p);
	print(" %x",**pp);
	
	print(" %x",(int)&m);
	print(" %x",(int)p);
	print(" %x",(int)*pp);
	p2=*pp;
	*p2=4;
	
	print(" %x",**pp);
	p2=get_mem(10);
	print("get_mem: 0x%08x:%d",(int)p2 ,*p2);
	get_mem2(&p2,10);
	print("get_mem2 addr: 0x%08x",(int)p2);
	print("get_mem2 content: %d",*p2);

	return 0;

}
void swap(int *a, int *b)
{
	//int *tmp=a;
	//a=b;
	//b=tmp;
	int tmp;
	tmp = *a;
	*a=*b;
	*b=tmp;

}
//
int main(void)
{
	int para;
	char data[80];
	int id;
	int i;
	int a=1;
	int b=2;
	my_mem_t *list,*list_previous;
	unsigned char *p;
	point_test();
	swap(&a,&b);
	//thread_test();
	para=1;
	m_task_create(function00,(void *)&para,&id);
	print("task id = 0x%x",id);
	
	print("For debug %d,%d",a,b); 
	print("For debug"); 
	print("For debug"); 
	print("For debug"); 
	print("For debug"); 
	for(i=0;i<5;i++)
	{
		p=malloc(2*i);
		memset(p,0,2*i);

		/* allocate a descriptor */
		list = (my_mem_t *)malloc(sizeof(my_mem_t));
		list->type = i;
		list->addr = (int)p;
		list->size = 2*i;
		list->next =NULL;

		 /* Attached the memory descriptor to the list */
		
		if(mem_list==NULL)
		{
		 	/* The list is now started with this element */
			mem_list = list;
		}	
		else
		{
			/* Add the new element on the top of the list */
			list->next = mem_list;
			mem_list= list;
		}
	}

	list = mem_list;
	while(list)
	{
		print("%d  0x%x   %d",list->type,list->addr,list->size);	
		list= list->next;

	}

	/* Look for the memory descriptor in the list */
	list = mem_list;
	list_previous =mem_list;
	while(list !=NULL)
	{
		if(list->type==1) break;
		list_previous = list;
		list=list->next;
	}
	if(!list) {
	print("list not found");
	return 0;
	}
	if(list==mem_list) mem_list = list->next;
	else list_previous->next = list->next;
	free((int *)list->addr);
	print("dealloc  0x%x",list->addr);
	
	 /* Deallocate the internal descriptor */
	 free(list);

	print("------------");
	list = mem_list;
	while(list)
	{
		print("%d  0x%x   %d",list->type,list->addr,list->size);	
		list= list->next;

	}

	memset(data,0,sizeof(data));
	while(read(0, data,sizeof(data)))
	{
		 write(1, data,strlen(data));
		 if(!strncmp(data,"quit",4)) break;
		 else 	print(">");
		 memset(data,0,sizeof(data));
	
	}

	print("sizeof data=%d",sizeof(data));
	para=0;
	m_task_delete(id);
	print("exit");
	return 0;

	
}
