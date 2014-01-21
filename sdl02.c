#include "my_sdl.h"
#include "q.h"
#include "ui.control.h"
//#include "/usr/src/linux-headers-3.8.0-29/include/linux/list.h"
//#include  "list0.h"

//typedef SDL_Thread task_t;

SDL_Surface *screen=NULL;
//SDL_Surface  *background=NULL;
SDL_Thread *thread;
SDL_sem *videoLock = NULL;
TTF_Font *font ; //=TTF_OpenFont("decker.ttf",28);



void sdl_stop()
{
	ui_message_delete();
	//ui_control_delete();
	SDL_DestroySemaphore( videoLock );

	//Free the surfaces
	SDL_FreeSurface( background );
	SDL_Quit();

}


typedef struct 
{
	char name[20];
	char *p;

}me_t;
me_t me;
char *gp;


int main(int argc,char *argv[])
{
	bool done = false;
	int 				threadReturnValue;
	int tickspersec;
	unsigned  long t,t2;

	strcpy(me.name,"wj");
	gp=me.name;
	print("me.name %s \n",me.name);
	
	print("me.p %s \n",gp);
//	return 0;
	//time_test();
	//th_test0();	
	//q_test2();
	//return 0;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	font=TTF_OpenFont("decker.ttf",28);
	screen = SDL_SetVideoMode(s_width,s_height,32,SDL_HWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	 print("\nSimple SDL_CreateThread test:");
	 
 	videoLock = SDL_CreateSemaphore( 1 );
	//background=IMG_Load("./background.png");
	
	//background=IMG_Load("./1.png");
	//show_surface( 0, 0, s_width,s_height, background );

	blit_test();
	my_widget_test();
	
	ui_message_init("myq",3);
	sdl_key_start();
	
	ui_control_init();
	live_control_init();
	live1_control_init();
	live2_control_init();
	live11_control_init();
	
	ui_control_start(UI_CONTROL("live.control"),NULL);
	while(1)
	{
		SDL_Delay(20);
	}
	//while(!done)
	
	SDL_DestroySemaphore( videoLock );

	//Free the surfaces
	//SDL_FreeSurface( background );
	SDL_Quit();
	return 0;

}

