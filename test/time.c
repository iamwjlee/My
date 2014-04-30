
#include "common.h"

#include <unistd.h>
#include <sys/time.h>
//#include "my_sdl.h"



unsigned long time_ticks_per_sec(void)
{
	return 1000;
}

inline unsigned long time_now()
{
     struct timeval tv;

     gettimeofday (&tv, NULL);
	 //print("%ld:%ld\n", tv.tv_sec, tv.tv_usec/1000);

     return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int time_after(unsigned long t1,unsigned long t2)
{
	int retVal;
	retVal = ((t1 > t2) ? 1 : 0);
	return retVal ;
}
unsigned long time_plus(unsigned long t1,unsigned long t2)
{
	unsigned long retVal;
	retVal = (unsigned long)(t1+t2);
	return retVal ;
}
unsigned long time_minus(unsigned long t1,unsigned long t2)
{
	unsigned long retVal;
	retVal = (unsigned long)(t1-t2);
	return retVal ;
}
void time_test(void)
{
	unsigned long t,t2;
	t=time_now();
	print("current time:%lu  0x%lx", t,t);
	sleep(5);
	t2=time_now();
	print("current time:%lu  0x%lx", t2,t2);
	print("time diff:%lumsec	0x%lxmsec ", t2-t,t2-t);

	print("5sec delay");
	t=time_now();
	while(1)
	{

		if(time_after(time_now(),t+5000))
			break;	
	}
	print("5sec ");
}


