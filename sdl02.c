#include "my_sdl.h"

int g_on =1;
int TestThread( void *ptr )
{
        int        cnt=0;
		while(g_on)
        {
                print( "\nThread counter: %d", cnt++);
                SDL_Delay(200);
        }

        return 0;
}

int main(int argc,char *argv[])
{
	bool done = false;

	SDL_Surface *screen=NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(800,600,32,SDL_HWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_RESIZABLE);

	SDL_Thread *thread;
	 int				 threadReturnValue;
	
	 print("\nSimple SDL_CreateThread test:");
	
	 // Simply create a thread
	 thread = SDL_CreateThread( TestThread,  (void *)NULL);
	
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
					case SDLK_q:
							g_on=0;
							SDL_WaitThread( thread, &threadReturnValue);
							print("Thread returned value:%d\n", threadReturnValue);
							//SDL_KillThread( thread );
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
	
	SDL_Quit();
	return 0;





}

