
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "q.h"
//#include "ui.control.h"

#define dprint(...)  printf(__VA_ARGS__)

//msg_queue_t *myQ;

/* find empty msg pointer for q_send  so we don't need to malloc and free everytime */
void *q_claim(msg_queue_t *q)
{
	msg_t *queue;
	int i;

	
	
	//
	#ifdef _my_debug
	queue=q->queue;
	for(i=0;i<q->count ;queue++, i++)
	{
		
		dprint(" q_claim[%d] : [%x][%d]\n",i,queue,queue->state);
	}
	#endif
	//
	
	queue=q->queue;
	for(i=0;i<q->count ;queue++, i++)
	{
		if(queue->state==RELEASED)
		{
			queue->state=CLAIMED;
			//dprint(" q_claim[%d] : [%x][%d]\n",i,queue,queue->state);
			return (queue->msg);
		}		
		else
		{
			//dprint(" ----------------q_claim fail ---------------------->\n");
		}
	}
	return NULL;

}

int q_release(msg_queue_t *q, void *msg)
{
	msg_t *queue;
	int i;
	queue=q->queue;
	for(i=0;i<q->count ;queue++, i++)
	{
		if(  (queue->msg==msg) && (queue->state==RECEIVED)  )
		{
			//d_dprint("q_release %d\n",*msg);
			queue->state=RELEASED;
			//memset(queue,0,sizeof(msg_t));
			return 0;
		}
		else if( (queue->msg==msg) && (queue->state==CLAIMED)  )
		{
			// remove link
			// 	queue->state=RELEASED;
			dprint(" \n\n -------------------link error -----------\n\n");

		}
	}
	return 1;

}

int q_send(msg_queue_t *q, void *msg)
{
	msg_t *queue;
	int i;
	queue=q->queue;
	for(i=0;i<q->count ;queue++, i++)
	{
		if(queue->state==CLAIMED)
		{
			queue->state=SENT; 
			queue->msg=msg;
			slink_add_back(q->slist,queue);
			return 0;
		} 
	}
	//free(msg);
	return 1;
}
void *q_receive(msg_queue_t *q)
{
	msg_t *queue;
	
	queue = slink_remove_front(q->slist);
	if(queue)
	{
		queue->state=RECEIVED;
		return queue->msg;
	}	
	else
		return NULL;
}

msg_queue_t *q_open(const char *name, int q_size ,int datasize)
{
	int i;
	msg_t *queue;
	msg_queue_t *q;

	q=(msg_queue_t *)calloc(1,sizeof(msg_queue_t));
	//dprint("q : %x\n",q);
	q->count=q_size;
	strcpy(q->name,name);
	
	q->queue=(msg_t *)calloc(1,sizeof(msg_t)*q->count);

	//dprint(" q->queue : %x\n",q->queue);
	queue=q->queue;
	for(i=0;i<q->count ;queue++, i++)
	{
 		queue->msg=(void *)calloc(1,datasize);
		//dprint(" queue->msg[%d] -[%x] \n",i,queue->msg);
	}
	
	queue=q->queue;
	for(i=0;i<q->count ;queue++, i++)
	{
		//dprint(" q->queue[%d] -[%x] [%x]\n",i,queue,queue->msg);
	}
	return q;
}
int q_init(const char *name, int q_size,msg_queue_t **qq)
{
	
	msg_queue_t *q;
	q=(msg_queue_t *)calloc(1,sizeof(msg_queue_t));
	q->count=q_size;
	strcpy(q->name,"myqueue");
	dprint("q_init: %x\n",(unsigned int)q->slist);
	q->queue=(msg_t *)calloc(1,sizeof(msg_t)*q->count);
	*qq=q;
	return 0;
}

msg_queue_t *q_open0(const char *name, int size )
{
	int i;
	msg_t *queue;
	msg_queue_t *q;
	q=(msg_queue_t *)calloc(1,sizeof(msg_queue_t));
	dprint("q : %x\n",(unsigned int)q);
	q->count=size;
	strcpy(q->name,name);
	
	q->queue=(msg_t *)calloc(1,sizeof(msg_t)*q->count);
	//dprint(" q->queue : %x\n",q->queue);
	queue=q->queue;
	for(i=0;i<q->count ;queue++, i++)
	{
		dprint(" q->queue[%d] -[%x] [%x]\n",i,(unsigned int)queue,(unsigned int)queue->msg);

	}
	
	return q;
}

typedef struct 
{
	int type;
	int key;
	int stamp;
}my_message_t;


int q_test2(void)
{
	msg_t *queue;
	int i;
	//int *msg;
	my_message_t *msg;
	msg_queue_t *q;
	int q_msg;
	
	q=q_open("myq",3,sizeof(my_message_t));
		
	msg=q_claim(q);
	
	if(msg) 
	{
		//*msg=11;
		msg->key=11;
		
		//dprint(" msg[%x]  [%d]\n",(unsigned int)msg,*msg);
		dprint(" msg[%x]  [%d]\n",(unsigned int)msg,msg->key);
		q_send(q,(void *)msg);
	}
	msg=q_claim(q);
	if(msg) 
	{
		
		//*msg=12;
		msg->key=12;
		//dprint(" msg[%x]  [%d]\n",(unsigned int)msg,*msg);
		
		dprint(" msg[%x]  [%d]\n",(unsigned int)msg,msg->key);
		q_send(q,(void *)msg);
	}
	msg=q_claim(q);
	if(msg) 
	{
		//*msg=13;
		msg->key=13;
		//dprint(" msg[%x]  [%d]\n",(unsigned int)msg,*msg);
		
		dprint(" msg[%x]  [%d]\n",(unsigned int)msg,msg->key);
		q_send(q,(void *)msg);
	}

	slink_foreach(queue, q->slist)
	{
		//dprint("\t queue[0x%x] queue->msg=%d	queue->state=%d \n",(unsigned int)queue,*(int *)queue->msg,queue->state);
		msg=(my_message_t *)queue->msg;
		dprint("\t queue[0x%x] queue->msg=%d	queue->state=%d \n",(unsigned int)queue,msg->key,queue->state);
	} 

	msg=(my_message_t *)q_receive(q);
	if(msg) 	dprint("q_receive=%d\n",msg->key);
	else dprint("q_receive=NULL\n");
	
	q_release(q, msg);

	msg=(my_message_t *)q_receive(q);
	if(msg) 	dprint("q_receive=%d\n",msg->key);
	else dprint("q_receive=NULL\n");
	q_release(q, msg);

	
	msg=(my_message_t *)q_receive(q);
	if(msg) 	dprint("q_receive=%d\n",msg->key);
	else dprint("q_receive=NULL\n");
	q_release(q, msg);

	
	msg=(my_message_t *)q_receive(q);
	if(msg) 	dprint("q_receive=%d\n",msg->key);
	else dprint("q_receive=NULL\n");
	if(q_release(q, msg) !=0) dprint("q_release fail\n");



	msg=q_claim(q);
	if(msg) 
	{
		msg->key=14;
		
		dprint(" msg[%x]  [%d]\n",(unsigned int)msg,msg->key);
		q_send(q,(void *)msg);
	}

		
	slink_foreach(queue, q->slist)
	{
		msg=queue->msg;
		dprint("\t queue[0x%x] queue->msg=%d	queue->state=%d \n",(unsigned int)queue,msg->key,queue->state);
	} 
	dprint("\n");
	
	queue=q->queue;
	for(i=0;i<q->count;queue++,i++)
	{
		msg=queue->msg;
		dprint("\t\t queue[0x%x] queue->msg=%d	queue->state=%d \n",(unsigned int)queue,msg->key,queue->state);
	}
	return 0;



}


int q_test(void)
{
	msg_t *queue;
	int i;
	int *msg;
	

	int *m; 
	
	//myQ=q_open("myq",3);
	q_init("myq2nd",3,&myQ);
	
	
	m=(int *)q_receive(myQ);
	if(m)
	{
		dprint("q_receive=%d\n",*m);
		free(m);
	}

	
	msg=calloc(1,sizeof(int));
	*msg=1;
	q_send(myQ,(void *)msg);
	msg=calloc(1,sizeof(int));
	*msg=2;
	q_send(myQ,(void *)msg);
	msg=calloc(1,sizeof(int));
	*msg=3;
	q_send(myQ,(void *)msg);
	#if 0
	msg=calloc(1,sizeof(int));
	*msg=4;
	q_send(myQ,(void *)msg);
	msg=calloc(1,sizeof(int));
	*msg=5;
	q_send(myQ,(void *)msg);
	#endif
	
	m=(int *)q_receive(myQ);
	if(m)
	{
		dprint("q_receive=%d\n",*m);
		free(m);
	}

	#if 1
	msg=calloc(1,sizeof(int));
	*msg=6;
	q_send(myQ,(void *)msg);
	
	msg=calloc(1,sizeof(int));
	*msg=7;
	q_send(myQ,(void *)msg);
	
	m=(int *)q_receive(myQ);
	if(m)
	{
		dprint("q_receive=%d\n",*m);
		free(m);
	}
	
	msg=calloc(1,sizeof(int));
	*msg=8;
	q_send(myQ,(void *)msg);
	#endif
	

	slink_foreach(queue, myQ->slist)
	{
		dprint("test[0x%x] test->msg=%d	state=%d \n",(unsigned int)queue,*(int *)queue->msg,queue->state);
	} 
	
	return 0;



}


