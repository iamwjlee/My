#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h> //sleep
#define print(f,...) printf(f"%s",##__VA_ARGS__,"\r\n")
#define log(...) printf(__VA_ARGS__)

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;




#endif

