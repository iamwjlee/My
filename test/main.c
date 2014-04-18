
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct my_mem_s
{
	int type;
	int addr;
	int size;
	struct my_mem_s *next;	

}my_mem_t;

static my_mem_t *mem_list=NULL;
int main(void)
{
	int i;
	my_mem_t *list,*list_previous;
	unsigned char *p;
	
	printf("hello\n");

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
		printf("%d  0x%x   %d\n",list->type,list->addr,list->size);	
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
	printf("list not found\n");
	return 0;
	}
	if(list==mem_list) mem_list = list->next;
	else list_previous->next = list->next;
	free((int *)list->addr);
	printf("dealloc  0x%x\n",list->addr);
	
	 /* Deallocate the internal descriptor */
	 free(list);

	printf("------------\n");
	list = mem_list;
	while(list)
	{
		printf("%d  0x%x   %d\n",list->type,list->addr,list->size);	
		list= list->next;

	}


	 
	return 0;

	
}
