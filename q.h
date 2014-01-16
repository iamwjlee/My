
#ifndef _Q_H_
#define _Q_H_

#include "slink.h"



typedef enum
{
	RELEASED=0,
	CLAIMED,
	RECEIVED,
	SENT,
} queue_state_t;

struct msg_s
{
	slink_t slink;
	queue_state_t state;
	void *msg;
	//unsigned char msg[4];
	
};
typedef struct msg_s msg_t;


struct msg_queue_s
{
	char name[20];
	int count;     
	msg_t *queue;
	slink_t *slist;  //list for msg_list_t
};
typedef struct  msg_queue_s msg_queue_t;

msg_queue_t *myQ;

int q_send(msg_queue_t *q, void *msg);
void *q_receive(msg_queue_t *q);
int q_init(const char *name, int size,msg_queue_t **qq);
msg_queue_t *q_open(const char *name, int q_size ,int m_size);

int q_test2(void);

#endif
