#include "common.h"


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
	mem_t *p1;
	
	p1 =(mem_t *)malloc(sizeof(mem_t));
	p1->type = type;
	p1->size = size;
	p1->next = NULL;
	p1->addr = (u32)malloc(size);
//	memset((char *)p1->addr,0,size);


	if(mem_list == NULL) 
		mem_list = p1;
	else
	{
		p1->next = mem_list;
		mem_list = p1;		
	}

	return (p1->addr);
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
	int i,j;
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


