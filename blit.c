#include "my_sdl.h"
#include "q.h"
#include "ui.control.h"
#include "widget.h"
//#include "/usr/src/linux-headers-3.8.0-29/include/linux/list.h"
//#include  "list0.h"


#define d_print(...)  dprint(__VA_ARGS__)

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

int flip_end(void)
{
	d_print("-flip_end-");
	//DFBCHECK(sur->Flip(sur, NULL, DSFLIP_WAITFORSYNC));
return 0;

}




void show_surface( int x, int y, int w,int h,SDL_Surface* source )
{
	d_print("\n source info : w:%d h:%d bpp:%d",  source->w, source->h, source->format->BitsPerPixel);
	d_print(" surface info : x:%d y:%d  w:%d h:%d",  x,y,w,h);

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

	source_images	= load_image( (const char *)*image);  // 
	if(source_images == NULL)
	{
		err("source_images is null :0x%x\n",(unsigned int)source_images);
	}
	//else
		
	//	print("source_images okay :0x%x\n",(unsigned int)source_images);
	
	
	if(dest_rect==NULL)
	{
		rect.x	= 0;
		rect.y= 0;
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

int gfx_blit_fill(int mode,gfx_rectangle_t *target_rect, unsigned int *source, gfx_rectangle_t *source_rect)
{

	if(*source==0) 
	{
		/* when widget_create(ex, button_create),  widget->background==0   */
		d_print(" gfx_blit_fill :  ------      no source(background)   ---------");
		return 0;
	}	


	if( ((*source>>24)&0xff) == 0x80 )
	{
		
		d_print(" gfx_blit_fill_color : 0x%x  ",*source);
		gfx_blit_fill_color( mode,target_rect,  (gfx_color_t *)source);
	}
	else
	{
		d_print(" gfx_blit_image : 0x%x ",*source);
		gfx_blit_image(target_rect, source, source_rect);
	}
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

int gfx_blit_label( int mode, char *text,gfx_rectangle_t *rect,  gfx_color_t color)
{
	SDL_Color my_color;
	SDL_Rect my_rect;

	my_color.r=color.argb.r;
	my_color.g=color.argb.g;
	my_color.b=color.argb.b;

	my_rect.x=rect->x;
	my_rect.y=rect->y;

	d_print( " gfx_blit_label[%s]",text);

	//rect->y+=font_dsc.height ;
	//rect->y+=8;

	if(mode)
	{
	}
	SDL_Surface *mytext = TTF_RenderText_Solid(font,text, my_color);
 	SDL_BlitSurface(mytext,NULL,screen,&my_rect);

	return 0;
}



int gfx_blit_restore(gfx_rectangle_t *rect, int *image, gfx_rectangle_t *src_rect)
{

	d_print("gfx_blit_restore");
	return 0;
}
int gfx_blit_capture(gfx_rectangle_t *rect, int *image, gfx_rectangle_t *src_rect)
{
	d_print("gfx_blit_capture");

	return 0;
}

blit_source_t 							out_border_test[8] =
										{
											(blit_source_t )DATADIR"border.out.NW.png",
											(blit_source_t )DATADIR"border.out.NE.png",
											(blit_source_t )DATADIR"border.out.N.png",
											(blit_source_t )DATADIR"border.out.SW.png",
											(blit_source_t )DATADIR"border.out.SE.png",
											(blit_source_t )DATADIR"border.out.S.png",
											(blit_source_t )DATADIR"border.out.W.png",
											(blit_source_t )DATADIR"border.out.E.png",
										};

blit_source_t 							*out_border_test2[8] =
										{
											(blit_source_t  *)DATADIR"border.out.NW.png",
											(blit_source_t *)DATADIR"border.out.NE.png",
											(blit_source_t *)DATADIR"border.out.N.png",
											(blit_source_t *)DATADIR"border.out.SW.png",
											(blit_source_t *)DATADIR"border.out.SE.png",
											(blit_source_t *)DATADIR"border.out.S.png",
											(blit_source_t *)DATADIR"border.out.W.png",
											(blit_source_t *)DATADIR"border.out.E.png",
										};

void pointer_array_test(unsigned int **bg)
{
	unsigned int *tmp;
	gfx_rectangle_t r={20,40,20,20};

	tmp=bg[0];
	gfx_blit_image(&r,tmp++,NULL);

	r.y+=20;
	gfx_blit_image(&r,tmp++,NULL);


}

int blit_test(void)
{
	unsigned int image;
	gfx_color_t c=GFX_COLOR(0x800096c8);
	gfx_rectangle_t 		rec 	= { 10, 10, 20, 20 };
	gfx_rectangle_t  r;
	FillRect(screen,0,0,s_width,s_height,0xf0303f);


	//gfx_blit_fill_color(0, &rec, &c ); 

	image=(unsigned int )DATADIR"border.out.NW.png";
	gfx_blit_image(&rec,&image,NULL);
	rec.y+=30;
	gfx_blit_fill(0,&rec,&image, NULL);

	//pointer_array_test(out_border_test2);

	
	// ttf test 
	
	//FillRect(screen,100,100,100,100,0x0000ff);
	SDL_Color color={0xff,0xff,0};
	TTF_Font *font=TTF_OpenFont("decker.ttf",28);
	SDL_Surface *text = TTF_RenderText_Solid(font, "Hello", color);
 	SDL_Rect rect = {400,20,0,0};//text position
 	SDL_BlitSurface(text,NULL,screen,&rect);

	//SDL_Flip(screen);

	
	//gfx_blit_fill(0,NULL, (unsigned int *)DATADIR"border.out.NW.png", NULL);

	#if 0
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
	#endif

}

