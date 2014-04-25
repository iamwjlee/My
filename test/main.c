#include "common.h"

//#include <pthread.h>
//#include <signal.h>
//#include <sys/types.h>
#include <unistd.h> //sleep


#include "task.h"
#include "sys.h"



typedef struct
{
	char *name;
	void (*func)(char *arg);

}command_t;


typedef struct my_mem_s
{
	int type;
	int addr;
	int size;
	struct my_mem_s *next;	

}my_mem_t;

static my_mem_t *mem_list=NULL;


//


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
	int m=1;
	int *p=&m;
	int **pp= &p;
	int *p2;
	
	print(" ---m=1---- ");
	print(" %d",m);
	print(" %x",*p);
	print(" %x",**pp);
	
	print(" %x",(int)&m);
	print(" %x",(int)p);
	print(" %x",(int)*pp);
	p2=*pp;
	*p2=4;
	print(" ---*p2=4---- ");
	print(" %d",m);
	print(" %x",*p);
	print(" %x",**pp);
	print(" --- **pp=5---- ");
	**pp=5;
	print(" %d",m);
	print(" %x",*p);
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
int get_key(char *data)
{
	int i=0;
	char key;
	//char data[30];
	memset(data,0,sizeof(data));
	while(1)
	{
		/*
		   current key buffer is 30. 
		   but suppose  buffer is 4 bytes and command is 10bytes
		 */  
		read(0,&key,1);   
		if(key=='\n') 
		{
			data[i++]='\0';
			print("data[%s]",data);
			//data1=data;		
			return 0;
		}
		else
		{
			data[i++]=key;
		}
		if(i>16) return 1;

	}

}


	/* for task */
	int id;
	int para;

void quit(char *arg)
{

	print("quit command");
	para=0;
	m_task_delete(id);
	print("exit");
	return ;
}

void test(char *arg)
{

	print("test command");
}


command_t cmds[]=
{
	{"quit",quit},
	{"test",test},
	{NULL,NULL}

};


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

int main(void)
{
	char data[80];
	char arg[2];
		char key[30];

	my_mem_t *list,*list_previous;
//	char key;
	int i;
	int a=1;
	int b=2;
	unsigned char *p;

	test_sys();
	return 0;
	

	log("wj\r\n");
	point_test();
	swap(&a,&b);
	//thread_test();
	m_task_test();
	while(1)
	{
		sleep(2);
	}
	return 0;

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

	while(1)
	{
		i=0;
		get_key(key);
		print("key=%s",key);
		while(cmds[i].name != NULL)
		{
			//print("key [%s] cmds.name [%s] i[%d]",key,cmds[i].name,i);
			if(!strcmp(key,cmds[i].name))
				cmds[i].func(arg);
			i++;

		}

		//if(!strcmp(key,"quit")) break;
	}
#if 0	
	i=0;
	memset(data,0,sizeof(data));
	while(1)`
	{

		read(0,&key,1);
		if(key=='\n') 
		{
			data[i++]=0;
			print("data[%s]",data);
			i=0;
		}
		else
		{
			data[i++]=key;
		}
		//print("data[%s]",data);

	}
#endif	
#if 0
	memset(data,0,sizeof(data));
	while(read(0, data,sizeof(data)))
	{
		write(1, data,strlen(data));
		
		if(!strncmp(data,"quit",4)) break;
		else 	print(">");
		memset(data,0,sizeof(data));
	
	}
#endif
	print("sizeof data=%d",sizeof(data));
	para=0;
	m_task_delete(id);
	print("exit");
	return 0;

	
}
