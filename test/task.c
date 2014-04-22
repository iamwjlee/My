
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//#include <signal.h>
//#include <sys/types.h>
#include <unistd.h> //sleep

#define print(f,...) printf(f"%s",##__VA_ARGS__,"\r\n")



int m_task_create(void *(*function)(void *),void *param,int *task_id)
{
	pthread_t t;
	pthread_create(&t,NULL,function,param);
	//pthread_join(t,&s);
	//print(" thread stop? %s ",(char *)s);
	print("t = 0x%x",(unsigned int)t);
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

//------------------------------------------

void *functionxx(void *p)
{
	while(1)
	{
	print(" child ");
	sleep(2);
	}

}

int thread_test(void)
{
	//void *s;
	pthread_t t;
	int a;
	pthread_create(&t,NULL,functionxx,(void *)&a);
	while(0)
	{
		print("parent");
		sleep(1);

	}
	//pthread_join(t,&s);
	//print(" thread stop? %s ",(char *)s);
	return 0;

}
//--------------------------------------------
