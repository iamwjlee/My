#include "my_sdl.h"
#include "q.h"
//#include "/usr/src/linux-headers-3.8.0-29/include/linux/list.h"
//#include  "list0.h"

typedef SDL_Thread task_t;

int g_on =1;
SDL_Surface *screen=NULL;
SDL_Surface  *background=NULL;
SDL_Thread *thread;
SDL_sem *videoLock = NULL;

task_t *task;
int TestThread( void *data )
{
        int        cnt=0;
		while(g_on)
        {
                print( "\nThread counter: %d", cnt++);
                SDL_Delay(20);
        }

        return 0;
}

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


int main(int argc,char *argv[])
{
	bool done = false;
	int 				threadReturnValue;
	int tickspersec;
	unsigned  long t,t2;

	time_test();
	th_test();	
	q_test2();
	return 0;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(800,600,32,SDL_HWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	 print("\nSimple SDL_CreateThread test:");

	 
	 videoLock = SDL_CreateSemaphore( 1 );
	 background=IMG_Load("./background.png");
	
	show_surface( 0, 0, background );
	 // Simply create a thread
	 task = SDL_CreateThread( TestThread,  (void *)NULL);
	
	 if( NULL == thread )
			printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	 else
	 {
	 }

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
						print("Exit this program\n");	
				    	done =  true;
				     	break;
					case SDLK_UP:
						print("up\n"); 
						
						break;

				  	case SDLK_DOWN:
						print("down\n"); 
						
						break;
					case SDLK_LEFT:
							print("left\n"); break;
					case SDLK_RIGHT:
							print("right\n"); break;
					case SDLK_a:
							if(!g_on) break;
							g_on=0;
							SDL_WaitThread( thread, &threadReturnValue);
							print("Thread returned value:%d\n", threadReturnValue);
							SDL_KillThread( thread );
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

	
	SDL_DestroySemaphore( videoLock );

	//Free the surfaces
	SDL_FreeSurface( background );
	SDL_Quit();
	return 0;





}

