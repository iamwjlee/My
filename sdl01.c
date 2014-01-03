#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
//#include "SDL/SDL_mixer.h"
#ifdef __cplusplus

#else
#if !defined(true) && ! defined(false)
typedef enum {false=0,true=1}  bool;

#endif
#endif
#define print(...) printf(__VA_ARGS__)


void FillRect(SDL_Surface *screen,int x, int y, int w, int h, int color) {
SDL_Rect rect = {x,y,w,h};
SDL_FillRect(screen, &rect, color);
}



int main(int argc,char *argv[])
{
	SDL_Rect r;
	bool done = false;
	SDL_Surface *screen=NULL;
	//SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	screen = SDL_SetVideoMode(800,600,16,SDL_HWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	//screen = SDL_SetVideoMode(600,480,32,SDL_SWSURFACE);

	SDL_Surface *image01;
	//SDL_Surface *image;
	//image01=SDL_LoadBMP("./hello.bmp");
	image01=IMG_Load("./1.png");
	if(image01 !=NULL)
	{
		//image= SDL_DisplayFormat(image01);
		//SDL_FreeSurface(image01);

		print("okay image loaded\n");
		
		SDL_PixelFormat *pixel_format=image01->format;
		int bpp = pixel_format->BitsPerPixel;
		int image_w = image01->w;
		int image_h = image01->h;
		int image_size = image_w * image_h * bpp;
		print("bpp[%d] w[%d] h[%d] size[%d]\n",bpp,image_w,image_h,image_size);
		
		r.x=300;
		r.y=100;
		r.w=image_w;
		r.h=image_h;
		SDL_BlitSurface(image01,NULL,screen,&r);
	}
	else
	 print(" image not loaded !!\n");

	
	
	FillRect(screen,100,100,100,100,0x0000ff);

	
	// ttf test 
	SDL_Color color={0xff,0xff,0};
	TTF_Font *font=TTF_OpenFont("decker.ttf",28);
	SDL_Surface *text = TTF_RenderText_Solid(font, "Hello", color);
 	SDL_Rect rect = {100,100,0,0};//text position
 	SDL_BlitSurface(text,NULL,screen,&rect);

	SDL_Flip(screen);

//	SDL_Delay(2000);

	//bool done =false;
while(!done)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
	    {

		    case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				  	case SDLK_ESCAPE:
				    	done =  true;
				     	break;
					case SDLK_UP:
						print("up\n"); 
						
						FillRect(screen,100,100,200,200,0xffffff);
						SDL_Flip(screen);
						break;

				  	case SDLK_DOWN:
						print("down\n"); 
						
						FillRect(screen,100,100,200,200,0x0000ff);
						SDL_Flip(screen);
						break;
					case SDLK_LEFT:
 						print("left\n"); break;
					case SDLK_RIGHT:
 						print("right\n"); break;
					case SDLK_q:
 						print("q\n"); break;
					case SDLK_w:
					case SDLK_e:
					case SDLK_r:
						
 						print("w\n"); break;
					case SDLK_1:
					case SDLK_2:
					case SDLK_3:
					case SDLK_4:
 						print("1\n"); break;
						
				}
				break;
		
			case SDL_VIDEORESIZE:
				{
				print("w:%d. h:%d \n",event.resize.w,event.resize.h);
				}
	      		break;
			case SDL_QUIT:
				print("window close\n");
				done=true;
				break;
					

		}
	}			

}
  SDL_FreeSurface(text);
	TTF_CloseFont(font);
	SDL_FreeSurface(image01);
	SDL_Quit();
	return 0;





}

