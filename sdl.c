#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
//#include "SDL/SDL_ttf.h"
//#include "SDL/SDL_mixer.h"
#ifdef __cplusplus

#else
#if !defined(true) && ! defined(false)
typedef enum {false=0,true=1}  bool;

#endif
#endif

int main(int argc,char *argv[])
{
	
	bool done = false;
	SDL_Surface *screen=NULL;
	//SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(800,600,32,SDL_HWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	//screen = SDL_SetVideoMode(600,480,32,SDL_SWSURFACE);

	SDL_Surface *hourglass;
	SDL_Surface *image;
	//hourglass=SDL_LoadBMP("./hello.bmp");
	hourglass=IMG_Load("./hourglass01.png");
	if(hourglass !=NULL)
	{
		//image= SDL_DisplayFormat(hourglass);
		//SDL_FreeSurface(hourglass);

		printf("okay image loaded\n");
	}
	else
	 printf(" image not loaded \n");
	SDL_BlitSurface(hourglass,NULL,screen,NULL);
	SDL_Flip(screen);
	SDL_Delay(2000);

//	SDL_Delay(2000);

	//bool done =false;
	while(!done)
	{
		SDL_Event event;
	  while(SDL_PollEvent(&event))
	  {
			switch(event.type)
 	    {
		  	case SDL_QUIT:
		    	done=true;
		      break;

        case SDL_KEYDOWN:
        	switch(event.key.keysym.sym)
          {
          	case SDLK_ESCAPE:
            	done =  true;
              break;
          }
          break;

				case SDL_VIDEORESIZE:
					{
          //char String[128];
          printf("w:%d. h:%d \n",event.resize.w,event.resize.h);
				}
          break;

	  	}
	  }			

	}
  
	SDL_FreeSurface(hourglass);
	SDL_Quit();
	return 0;





}

