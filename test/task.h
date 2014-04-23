
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//#include <signal.h>
//#include <sys/types.h>
#include <unistd.h> //sleep

#ifndef __TASK_H
#define __TASK_H

/*
	pthread_create wraper
*/
int m_task_create(void *(*function)(void *),void *param,int *task_id);
int m_task_delete(int task_id);

enum
{

 a,
 b

};
#endif
