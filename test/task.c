#include "common.h"
#include <pthread.h>
//#include <signal.h>
//#include <sys/types.h>
#include <unistd.h> //sleep

#include "sys.h"

/*
	2nd job

	simple pthread wraper


*/


int m_task_create(void *(*function)(void *),void *param,int *task_id)
{
	pthread_t t;
	pthread_create(&t,NULL,function,param);
	//print("t = 0x%x",(unsigned int)t);
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
