#include "my_sdl.h"
#include "q.h"
#include "ui.control.h"
#include "widget.h"
//#include "/usr/src/linux-headers-3.8.0-29/include/linux/list.h"
//#include  "list0.h"

//typedef SDL_Thread task_t;

SDL_Surface  *background=NULL;
//SDL_Thread *thread;
//SDL_sem *videoLock = NULL;
//SDL_Surface *load_image( const char *name );



SDL_Surface *load_image( const char *name );


gfx_color_t GFX_COLOR(U32 value)
{
	gfx_color_t				color = { .value = value };

	return(color);
}



void show_surface( int x, int y, int w,int h,SDL_Surface* source )
{
	print("Surface : w:%d h:%d bpp:%d\n",  source->w, source->h, source->format->BitsPerPixel);

    SDL_SemWait( videoLock );

    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

	/*
   	if(w==0 && h==0 ) 
    SDL_BlitSurface( source, NULL, screen, &offset );
	else	
	{
	offset.w=w;
	offset.h=h;
	SDL_SoftStretch( source, NULL, screen, &offset );
	}
	*/
	if(w!=source->w || h !=source->h)
	{
		
		offset.w=w;
		offset.h=h;
		SDL_SoftStretch( source, NULL, screen, &offset );
	}		
	else
	{
    	SDL_BlitSurface( source, NULL, screen, &offset );

	}
		

    //Update the screen
    SDL_Flip( screen );

    //Unlock
    SDL_SemPost( videoLock );
}

void FillRect(SDL_Surface *screen,int x, int y, int w, int h, unsigned int  color) {
SDL_Rect rect = {x,y,w,h};
SDL_FillRect(screen, &rect, color);
}



int gfx_blit_fill_color( blit_mode_t mode,gfx_rectangle_t *rect,  gfx_color_t *color)
{
	/*  
		Need to get the color_type ARGB4444,ARGB1555... ?
		Need to set DSDRAW_BLEND ?
		sur->SetDrawingFlags( sur, DSDRAW_NOFX );

	*/

	/*
		
	BLIT_MODE_COPY
	BLIT_MODE_BLEND

	*/

	unsigned int c=color->value;
	gfx_rectangle_t g=*rect;
	SDL_Rect s;

	s.x = g.x;
	s.y = g.y;
	s.w = g.w;
	s.h = g.h;

	
	SDL_FillRect(screen,&s, c);
	return 0;

}

int gfx_blit_image(gfx_rectangle_t *dest_rect, unsigned int *image, gfx_rectangle_t *src_rect)
{
	int w,h;
	SDL_Rect			rect;
	SDL_Surface *source_images;

	//return 0;
	
	source_images	= load_image( (const char *)*image);
	
	//source_images->GetSize( source_images, &w, &h );
	/*
	if(!src_rect)
	{
		rect.x	= 0;
		rect.x= 0;
		rect.w		=w;
		rect.h	= h;
	}
	else
	{
		rect.x	= src_rect.x;
		rect.x= src_rect.y;
		rect.w		=src_rect.w;
		rect.h	= src_rect.h;
	}
*/
	
	if(!dest_rect)
	{
		rect.x	= 0;
		rect.x= 0;
		rect.w		=source_images->w;
		rect.h	= source_images->h;
	}
	else
	{
		rect.x	= dest_rect->x;
		rect.y= dest_rect->y;
		rect.w		=dest_rect->w;
		rect.h	= dest_rect->h;
	}
	
	show_surface( rect.x,rect.y,rect.w,rect.h,source_images );


	return 0;

}

SDL_Surface *load_image( const char *name )
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
  //  loadedImage = SDL_LoadBMP( name );
		
    loadedImage = IMG_Load( name );
		

    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
				
        //If the image was optimized just fine
        if( optimizedImage != NULL )
        {
            //Map the color key with white color
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xff, 0xFF, 0xFF );

            //Set all pixels of color R 0xff, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }

				
    }

    //Return the optimized image
    return optimizedImage;
}


int blit_test(void)
{
	
	gfx_color_t c=GFX_COLOR(0x800096c8);
	gfx_rectangle_t 		rec 	= { 10, 300, 234, 72 };
	gfx_rectangle_t  r;
	FillRect(screen,0,0,s_width,s_height,0x0000ff);


	gfx_blit_fill_color(0, &rec, &c ); 

	
	//gfx_blit_image(NULL,(unsigned int *)DATADIR"border.out.NW.png",NULL);


	
	background=load_image(DATADIR"border.out.NW.png");
	show_surface( 30, 30, background->w,background->h, background );
	
	background=load_image(DATADIR"border.out.NE.png");
	show_surface( 30+200-20, 30, background->w,background->h, background );

	background=load_image(DATADIR"border.out.N.png");
	show_surface( 30+20, 30, 200-20-20,background->h, background );


	background=load_image(DATADIR"border.out.SW.png");
	show_surface( 30, 30+400-32,background->w,background->h, background );

	background=load_image(DATADIR"border.out.SE.png");
	show_surface( 30+200-32, 30+400-32, background->w,background->h, background );

	background=load_image(DATADIR"border.out.S.png");
	show_surface( 30+32, 30+400-32, 200-32-32,background->h, background );


	
	background=load_image(DATADIR"border.out.W.png");
	show_surface( 30, 30+20, background->w,400-20-32, background );

	background=load_image(DATADIR"border.out.E.png");
	show_surface( 30+200-20, 30+20, background->w,400-20-32, background );

}

