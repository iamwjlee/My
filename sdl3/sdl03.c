#include "my_sdl.h"
#include "q.h"
#include "ui.control.h"
//#include "/usr/src/linux-headers-3.8.0-29/include/linux/list.h"
//#include  "list0.h"

#include "gt.h"
#include "my_view.h"
#include "get_key.h"
#include "my_view2.h"
#define d_print(...)  dprint(__VA_ARGS__)

/*

	Need of Event Call or Callback
	Necessity of Event Driven,Callback,Asynchronous, Non Blocking
		event -> int (*callback)(void);
	
	Repeat Codes for key pressing


*/


void sdl_stop()
{
	ui_message_delete();
	
	gt_exit();

}



extern int  datalist_test(void);

int main(int argc,char *argv[])
{
	//int *test_p = NULL;
	//bool done = false;
	//int 				threadReturnValue;
	//int tickspersec;
	//unsigned  long t,t2;

	if(argc>1)
	{
		while(--argc)
			printf("argument[%s]\r\n",argv[argc]);

		assert(0);
		//time_test();
		//th_test0(); 
		//q_test2();
		//datalist_test();
		t_zlist();
		t_container();
		tt_xlist();
		return 0;

	}
	
	err(" Good Luck!");

	gt_init();

	//my_widget_test(0);
	
	ui_message_init("myq",3);
	sdl_key_start();
	
	ui_view_init();
	ui_control_init();

	my_view2_init();
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

