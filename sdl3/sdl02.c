#include "my_sdl.h"
#include "q.h"
#include "ui.control.h"
//#include "/usr/src/linux-headers-3.8.0-29/include/linux/list.h"
//#include  "list0.h"

#include "gt.h"
#include "my_view.h"
#define d_print(...)  dprint(__VA_ARGS__)


//typedef SDL_Thread task_t;

//SDL_Surface *screen=NULL;
//SDL_Surface  *background=NULL;
//SDL_Thread *thread;
//SDL_sem *videoLock = NULL;
//TTF_Font *font ; //=TTF_OpenFont("decker.ttf",28);



void sdl_stop()
{
	ui_message_delete();
	
	gt_exit();

}



extern int  datalist_test(void);

int main(int argc,char *argv[])
{
	int *test_p = NULL;
	bool done = false;
	//int 				threadReturnValue;
	//int tickspersec;
	//unsigned  long t,t2;

	if(argc>1)
	{
		while(--argc)
			printf("argument[%s]\r\n",argv[argc]);
		
		gt_test();
		return 0;

	}
	
	//*test_p=1234;
	err(" Good Luck!");
	datalist_test();
	
	//time_test();
	//th_test0();	
	//q_test2();
	//return 0;
	
	//while(1)  	{	SDL_Delay(20);	}
	//return 0;
	gt_init();
	//background=IMG_Load("./background.png");
	
	//background=IMG_Load("./1.png");
	//show_surface( 0, 0, s_width,s_height, background );

	//blit_test();
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
		
			
		SDL_Delay(10);
	}
	//while(!done)
	

	//Free the surfaces
	//SDL_FreeSurface( background );
	gt_exit();
	err(" Exit ");
	
	SDL_Delay(1000);
	return 0;

}

