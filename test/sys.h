#ifndef __SYS_H
#define __SYS_H

#include "common.h"


u32 mem_alloc(int type,int size);
int mem_dealloc(u32 addr);
int mem_show(void);

int test_sys(void);

#endif
