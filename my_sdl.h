
#ifndef _MY_SDL_H
#define _MY_SDL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "time.h"
//#include "SDL/SDL_mixer.h"
#ifdef __cplusplus
extern "C" {
#else
#if !defined(true) && ! defined(false)
typedef enum {false=0,true=1}  bool;
#endif
#endif

#ifndef null
#define null NULL
#endif

typedef  unsigned int 		gfx_bitmap_t;
typedef   unsigned int		blit_source_t;
typedef unsigned int  osclock_t;

typedef unsigned int	U32;
typedef signed int	S32;
typedef signed short S16;
typedef unsigned short U16;
typedef unsigned char  U8;

#define print(...) printf(__VA_ARGS__)
#define err(f,...) printf("%s"f"%s", "\e[31m", ##__VA_ARGS__, "\e[0m \n")  //red
#define print32(f,...) printf("%s"f"%s", "\e[32m", ##__VA_ARGS__, "\e[0m \n")  //green
#define print33(f,...) printf("%s"f"%s", "\e[33m", ##__VA_ARGS__, "\e[0m")  //brown
#define print34(f,...) printf("%s"f"%s", "\e[34m", ##__VA_ARGS__, "\e[0m \n")  //blue
#define print35(f,...) printf("%s"f"%s", "\e[35m", ##__VA_ARGS__, "\e[0m")  //purple 
#define print36(f,...) printf("%s"f"%s", "\e[36m", ##__VA_ARGS__, "\e[0m")  //cyan
#define print37(f,...) printf("%s"f"%s", "\e[37m", ##__VA_ARGS__, "\e[0m")  //grey

#define print46(f,...) printf("%s"f"%s", "\e[46m", ##__VA_ARGS__, "\e[0m")  //cyan background
#define print47(f,...) printf("%s"f"%s", "\e[47m", ##__VA_ARGS__, "\e[0m \n")  //grey background

#define print3744(f,...) printf("%s"f"%s", "\e[37m \e[44m", ##__VA_ARGS__, "\e[0m \n")  //grey + blue background
#define print3745(f,...) printf("%s"f"%s", "\e[37m \e[45m", ##__VA_ARGS__, "\e[0m \n")  //grey + purple background
#define print3740(f,...) printf("%s"f"%s", "\e[37m \e[40m", ##__VA_ARGS__, "\e[0m")  //grey + black background

#ifdef __cplusplus
}
#endif


#endif
