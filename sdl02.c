#include "my_sdl.h"
#include "q.h"
#include "ui.control.h"
//#include "/usr/src/linux-headers-3.8.0-29/include/linux/list.h"
//#include  "list0.h"

//typedef SDL_Thread task_t;

SDL_Surface *screen=NULL;
SDL_Surface  *background=NULL;
SDL_Thread *thread;
SDL_sem *videoLock = NULL;


void show_surface( int x, int y, SDL_Surface* source )
{
    //Lock
    SDL_SemWait( videoLock );

    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, NULL, screen, &offset );

    //Update the screen
    SDL_Flip( screen );

    //Unlock
    SDL_SemPost( videoLock );
}

void sdl_stop()
{
	ui_message_delete();
	//ui_control_delete();
	SDL_DestroySemaphore( videoLock );

	//Free the surfaces
	SDL_FreeSurface( background );
	SDL_Quit();

}


int main(int argc,char *argv[])
{
	bool done = false;
	int 				threadReturnValue;
	int tickspersec;
	unsigned  long t,t2;

	//time_test();
	th_test0();	
	q_test2();
	//return 0;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(800,600,32,SDL_HWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	 print("\nSimple SDL_CreateThread test:");

	 
	 videoLock = SDL_CreateSemaphore( 1 );
	 background=IMG_Load("./background.png");
	
	show_surface( 0, 0, background );

	
	ui_message_init("myq",3);
	sdl_key_start();
	
	ui_control_init();
	live_control_init();
	
	ui_control_start(UI_CONTROL("live.control"),NULL);
	while(1)
	{
		SDL_Delay(20);
	}
	//while(!done)
	
	SDL_DestroySemaphore( videoLock );

	//Free the surfaces
	SDL_FreeSurface( background );
	SDL_Quit();
	return 0;

}

