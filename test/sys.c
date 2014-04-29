#include "common.h"

/*
	1st job
	memory alloc function
	which is listed

*/   


typedef struct mem_s
{
	int type;
	int addr;
	int size;
	struct mem_s *next;	

}mem_t;

static mem_t *mem_list=NULL;



u32 mem_alloc(int type,int size)
{	
	mem_t *p;
	/* allocate a descriptor */	
	p =(mem_t *)malloc(sizeof(mem_t));
	p->type = type;
	p->size = size;
	p->next = NULL;
	p->addr = (u32)malloc(size);
//	memset((char *)p->addr,0,size);

	/* Attached the memory descriptor to the list */
	if(mem_list == NULL) 
	{
		/* The list is now started wiht this element */
		mem_list = p;
	}	
	else
	{
		/* Add the new element on the top of the list */
		p->next = mem_list;
		mem_list = p;		
	}

	return (p->addr);
}

int mem_dealloc(u32 addr)
{
	mem_t *p0,*p; /*p0 = previous */
	p0=p=mem_list;

	while(p)
	{
		if(p->addr==addr) break;
		p0=p;
		p=p->next;
	}
	if(p)
	{

		if(p==mem_list) mem_list=p->next;
		else p0->next=p->next;
		
		free((void *)p->addr);
		/* Deallocate the internal descriptor */
		free(p);
	}
	else
	{
		print("memory not found[0x%x]",addr);
		return 1;
	}
	return 0;

}

int mem_show(void)
{
	mem_t *p;
	p=mem_list;
	while(p)
	{
		print("addr[0x%x] size[0x%x] type[%d]",p->addr,p->size,p->type);
		p=p->next;
	
	}
	return 0;
}


int test_sys(void)
{
	int i;
	//int j;
	u32 addr[10];
	for(i=1;i<10;i++)
	{	
		addr[i]=mem_alloc(i,i*2);
		//memset((char *)addr[i],0,i*2);
		print("%d : addr=0x%x",i,addr[i]);
		//for(j=0;j<i*2;j++)
		//print("-> %d",*((char *)addr[i]+j)	);	
	}	

	mem_show();
	mem_dealloc(addr[0]);
	mem_dealloc(addr[4]);
	mem_dealloc(addr[9]);
	mem_show();
	return 0;

}

/* ------------------------------- */


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

int test_get_mem(void)
{

	int *p;

	p=get_mem(10);
	print("get_mem: 0x%08x:%d",(int)p ,*p);
	get_mem2(&p,10);
	print("get_mem2 addr: 0x%08x",(int)p);
	print("get_mem2 content: %d",*p);

	return 0;
}
