/*
	gt.h
	gt driver for SDL lib

*/


#ifndef _GT_H_
#define _GT_H_

#include "widget.h"

#if 0
typedef enum
{
	GfxALIGNMENT_NONE,
	GfxALIGNMENT_TOP				= 0x0001,
	GfxALIGNMENT_MIDDLE				= 0x0002,
	GfxALIGNMENT_BOTTOM				= 0x0004,
	GfxALIGNMENT_TRAIL_V			= 0x0008,

	GfxALIGNMENT_LEFT				= 0x0010,
	GfxALIGNMENT_CENTER				= 0x0020,
	GfxALIGNMENT_RIGHT				= 0x0040,
	GfxALIGNMENT_TRAIL_H			= 0x0080,

	GfxALIGNMENT_ALIGN				= 0x1000,
	GfxALIGNMENT_DOCK				= 0x2000,

	GfxALIGN_TOP					= GfxALIGNMENT_ALIGN | GfxALIGNMENT_TOP,
	GfxALIGN_MIDDLE					= GfxALIGNMENT_ALIGN | GfxALIGNMENT_MIDDLE,
	GfxALIGN_BOTTOM					= GfxALIGNMENT_ALIGN | GfxALIGNMENT_BOTTOM,
	GfxALIGN_VERTICAL_TRAIL			= GfxALIGNMENT_ALIGN | GfxALIGNMENT_TRAIL_V,

	GfxALIGN_LEFT					= GfxALIGNMENT_ALIGN | GfxALIGNMENT_LEFT,
	GfxALIGN_CENTER					= GfxALIGNMENT_ALIGN | GfxALIGNMENT_CENTER,
	GfxALIGN_RIGHT					= GfxALIGNMENT_ALIGN | GfxALIGNMENT_RIGHT,
	GfxALIGN_HORIZONTAL_TRAIL		= GfxALIGNMENT_ALIGN | GfxALIGNMENT_TRAIL_H,

	GfxDOCK_TOP						= GfxALIGNMENT_DOCK | GfxALIGNMENT_TOP,
	GfxDOCK_BOTTOM					= GfxALIGNMENT_DOCK | GfxALIGNMENT_BOTTOM,
	GfxDOCK_LEFT					= GfxALIGNMENT_DOCK | GfxALIGNMENT_LEFT,
	GfxDOCK_RIGHT					= GfxALIGNMENT_DOCK | GfxALIGNMENT_RIGHT,
	GfxDOCK_FILL					= GfxALIGNMENT_DOCK | GfxALIGNMENT_MIDDLE,
	GfxDOCK_PHANTOM					= 0x80000000,
	GfxALIGN_SAME_AS_LAST			= 0x40000000,
	GfxALIGN_VERTICAL_TRAIL_BEFORE	= 0x20000000,

} gfx_align_t;

typedef enum
{
	PEN_ATTRIBUTE_NO_ADVANCE			= 0x01,
	PEN_ATTRIBUTE_FIXED_WIDTH			= 0x02,
	PEN_ATTRIBUTE_MULTI_LINES			= 0x04,
	PEN_ATTRIBUTE_BOLD	 				= 0x08,
	PEN_ATTRIBUTE_SCROLLABLE			= 0x10,
	PEN_ATTRIBUTE_RIGHT_TO_LEFT			= 0x20,
	PEN_ATTRIBUTE_UNICODE_BMP			= 0x80,
} gfx_pen_attribute_t;



typedef enum
{
	BLIT_MODE_COPY			= 0,
	BLIT_MODE_BLEND			= 0x01,
	BLIT_MODE_TRIG			= 0x10,
	BLIT_DELETE_SOURCE		= 0x20,
	BLIT_MODE_TRIG_X		= 0x40,
	BLIT_MODE_UNDEFINED		= 0x80,
	
} blit_mode_t;



typedef union
{
	U32						value;
	struct
	{
		U8					b;
		U8					g;
		U8					r;
		U8					a;
	} argb;
} gfx_color_t;

typedef struct
{
	S16						x;
	S16						y;
} gfx_point_t;

typedef struct	/* compatable with STGXOBJ_Rectangle_t */
{
	unsigned int						x;
	unsigned int						y;
	unsigned int			w;
	unsigned int			h;
} gfx_rectangle_t;


struct gfx_pen_s
{
	gfx_pen_attribute_t		attribute;
	gfx_color_t				forecolor;
	//gfx_font_t				*font;		/* should be defined before use */
	//gfx_bitmap_t			*target;	/* should be defined before use */
	//STGXOBJ_Palette_t		*palette;
	gfx_rectangle_t			cursor;
	gfx_align_t				align;

	struct
	{
		U32					glyph;
		gfx_rectangle_t		cursor;
		const char			*word;
	} last;

	struct
	{
		gfx_rectangle_t				granted;
		gfx_rectangle_t				line;
	} area;										/* should be defined before use */
};
typedef struct gfx_pen_s				gfx_pen_t;
#endif


extern  SDL_Surface *screen;
extern SDL_sem *screenLock;
extern TTF_Font *font ; //=TTF_OpenFont("decker.ttf",28);




int gt_init(void);
int gt_exit(void);

gfx_color_t GFX_COLOR(U32 value);

int flip_end(void);

SDL_Surface *load_image( const char *name );

int gfx_blit_fill(int mode,gfx_rectangle_t *target_rect, unsigned int *source, gfx_rectangle_t *source_rect);
int gfx_blit_fill_color( blit_mode_t mode,gfx_rectangle_t *rect,  gfx_color_t *color);
int gfx_blit_image(gfx_rectangle_t *dest_rect, unsigned int *image, gfx_rectangle_t *src_rect);




int gfx_blit_label( int mode, const char *text,gfx_rectangle_t *rect,  gfx_color_t color);
void gfx_printf(gfx_pen_t *pen, const char *format, ...);


int gfx_blit_restore(gfx_rectangle_t *rect, int *image, gfx_rectangle_t *src_rect);
int gfx_blit_capture(gfx_rectangle_t *rect, int *image, gfx_rectangle_t *src_rect);
int gfx_new_puts(gfx_pen_t *pen,const char *string);



int gt_test(void);
#endif

