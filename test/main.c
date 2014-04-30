#include "common.h"

//#include <pthread.h>
//#include <signal.h>
//#include <sys/types.h>
#include <unistd.h> //sleep


#include "task.h"
#include "sys.h"
#include "counter_task.h"
#include "get_key.h"
#include "q.h"
#include "time.h"



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

void xx(u8 *buf)
{
	int i;
	u8 j=0;
	for(i=0;i<1024;i++)
		*(buf+i)=j++;

}
void file_test(void)
{
	
	FILE *f;
	int i;
	u8 buffer[1024];
	print("file test size[%d]",sizeof(buffer));
	f=fopen("wj.bin","wb");

	xx(buffer);
	for(i=0;i<1024;i++)
	{
	fwrite(buffer,sizeof(char)*1024,1,f);
	}
	print(" end of write");
	fclose(f);
	print("file close");

}


int main(void)
{

	int a=1;
	int b=2;

	log("wj concep! [%d] [%d]\r\n",sizeof(unsigned long),sizeof(unsigned int));
	print("swap test");
	print("a=%d b=%d",a,b);
	swap(&a,&b);
	print("a=%d b=%d",a,b);

	//point_test();
	//test_sys();
	//my_counter_task_test();
	//test_get_string();
	//q_test();
	fifo_test();
	//file_test();
	time_test();
	get_key();
	return 0;
	

	while(1)
	{
		sleep(2);
	}
	return 0;



	print("exit");
	return 0;

	
}
