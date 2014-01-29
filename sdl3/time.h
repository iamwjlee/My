#ifndef _TIME_H_
#define _TIME_H_

#include <stdio.h> //printf
#include <stdlib.h>  //calloc,malloc
#include <string.h>  //strcpy,memset

#ifdef __cplusplus
extern "C" {
#endif

unsigned long time_ticks_per_sec(void);

inline unsigned long time_now();
int time_after(unsigned long t1,unsigned t2);
unsigned long time_plus(unsigned long t1,unsigned t2);
unsigned long time_minus(unsigned long t1,unsigned t2);






#ifdef __cplusplus
}
#endif
#endif 

