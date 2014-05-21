#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "SDL.h"
//#include "PDL.h"
//#include "SDL_mixer.h"
#include <SDL.h>
#include <SDL_thread.h>

void create_tone(void *userdata, Uint8 *stream, int len) ;
 
int main(int argc, char *argv[]) {
 
  SDL_Surface *screen;
  SDL_Event event;
  int done = 0;
 
  /* Audio Setup */
  SDL_AudioSpec *desired, *obtained;
  SDL_AudioSpec *hardware_spec;
 
  desired = (SDL_AudioSpec*)malloc(sizeof(SDL_AudioSpec));
  obtained = (SDL_AudioSpec*)malloc(sizeof(SDL_AudioSpec));
 
 
  desired->freq=22050;
  desired->format=AUDIO_S16LSB;
  desired->channels=0;
  desired->samples=8192;
  desired->callback=create_tone;
  desired->userdata=NULL;
 
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  //PDL_Init(0) ;
 
  /* Open the audio device */
  if ( SDL_OpenAudio(desired, obtained) < 0 ){
    fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
    exit(-1);
  }
  /* desired spec is no longer needed */
  free(desired);
  desired=NULL;
  hardware_spec=obtained;
 
  SDL_PauseAudio(0) ;
 
  screen = SDL_SetVideoMode(320, 240, 0, 0);
 
  while(!done) {
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
          done = 1;
          break;
      }
    }
    SDL_Delay(50);
  }
  SDL_PauseAudio(1);
 
  //PDL_Quit() ;
  SDL_Quit();
 
}
 
void create_tone( void *userdata, Uint8 *stream, int len ) {
  static double angle = 0.0 ;
  int i = 0 ;
  fprintf( stderr, "Filling %d\n", len ) ;
  for(i=0;i<len;i++) {
    *stream++ = 255*cos(angle) ; // I think that this should be 128 * cos(angle) as cos is (-1,1)
    angle += 3.14159/100 ;       // and a Uint8 is only 8 bits (256 values)
    if( angle > 2.0*3.14159 ) {
      angle -= 2.0*3.14159 ;
    }
  }
}
