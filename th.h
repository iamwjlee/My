#ifndef _TH_H_
#define _TH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my_sdl.h"
#include "slink.h"

#define TASK_PRIORITY					99
#define TASK_STACK_SIZE					(1 * 1024)
#define TIMEOUT_INFINITY    ((unsigned long *)NULL)
#define TIMEOUT_IMMEDIATE   ((unsigned int *)1)

typedef SDL_Thread task_t;
typedef int task_flags_t;



task_t *task_create (int (*function)(void*),void* param,int stack_size,int priority,const char* name,task_flags_t flags);
int task_wait(task_t *task, int ntasks, unsigned long *timeout);
int task_delete(task_t *task);
void th_test();



#endif
