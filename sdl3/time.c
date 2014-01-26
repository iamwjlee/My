#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my_sdl.h"




inline unsigned long time_now()
{
     struct timeval tv;

     gettimeofday (&tv, NULL);
	 //print("%ld:%ld\n", tv.tv_sec, tv.tv_usec/1000);

     return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int time_after(unsigned long t1,unsigned t2)
{
	int retVal;
	retVal = ((t1 > t2) ? 1 : 0);
	return retVal ;
}
unsigned long time_plus(unsigned long t1,unsigned t2)
{
	unsigned long retVal;
	retVal = (unsigned long)(t1+t2);
	return retVal ;
}
unsigned long time_minus(unsigned long t1,unsigned t2)
{
	unsigned long retVal;
	retVal = (unsigned long)(t1-t2);
	return retVal ;
}
void time_test()
{
	unsigned long t,t2;
	t=time_now();
	print("current time:%ld  0x%lx\n", t,t);
	SDL_Delay(100);
	t2=time_now();
	print("current time:%ld  0x%lx\n", t2,t2);
	print("time diff:%ldmsec	0x%lxmsec \n", t2-t,t2-t);
}


