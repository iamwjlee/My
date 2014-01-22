#ifndef __GxLIB_GFX__WIDGET_TYPES_H_
#define __GxLIB_GFX__WIDGET_TYPES_H_

/* includes ------------------------------------------------------------------- */
#include "dlink.h"

//#include <directfb.h>
 
#ifdef __cplusplus
extern "C" {
#endif

/* constants ------------------------------------------------------------------ */

#define CLIENT_BODY 0x80c0f0f0
#define BODY_COLOR 0x800070A0
#define LABEL_COLOR 0x80ffffff

#define BLIT_SOURCE_NONE				0x80000000

#define T_DOCK							.align = GfxDOCK_TOP
#define B_DOCK							.align = GfxDOCK_BOTTOM
#define L_DOCK							.align = GfxDOCK_LEFT
#define R_DOCK							.align = GfxDOCK_RIGHT
#define F_DOCK							.align = GfxDOCK_FILL
 
#define WT_DOCK							.widget.align = GfxDOCK_TOP
#define WB_DOCK							.widget.align = GfxDOCK_BOTTOM
#define WL_DOCK							.widget.align = GfxDOCK_LEFT
#define WR_DOCK							.widget.align = GfxDOCK_RIGHT
#define WF_DOCK							.widget.align = GfxDOCK_FILL
 
 
#define WL_ALIGN						.widget.align = GfxALIGN_LEFT
#define WR_ALIGN						.widget.align = GfxALIGN_RIGHT
#define W_RECT							.widget.rect
#define W_PAD							.widget.pad
#define W_BACK							.widget.background

/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */


typedef enum
{
	_DISPLAY_HD,
	_DISPLAY_SD,
	DISPLAY_HDMI,
} display_id_t;

#define DISPLAY_HD_MAX_WIDTH			1024
#define DISPLAY_HD_MAX_HEIGHT			768

#define KEYPAD_MAX_CHARACTER			16

typedef enum
{
	KEY_NONE							= 0x00,
	KEY_MUTE =1,
	
	KEY_UP =2,
	KEY_DOWN=3,
	KEY_VFORMAT,
	KEY_TV_STB,

	KEY_OK								= 0x10,
	KEY_MENU,
	KEY_EXIT,

	KEY_LEFT,
	KEY_RIGHT,
	KEY_PAGE_UP,
	KEY_PAGE_DOWN,

	KEY_PANEL_LEFT,
	KEY_PANEL_RIGHT,

	KEY_CH_UP							= 0x20,
	KEY_CH_DOWN,
	KEY_PREVIOUS,
	KEY_VOLUME_UP,
	KEY_VOLUME_DOWN,
	KEY_TV_RADIO,

	KEY_NUMBER_0						= 0x30,
	KEY_NUMBER_1,
	KEY_NUMBER_2,
	KEY_NUMBER_3,
	KEY_NUMBER_4,
	KEY_NUMBER_5,
	KEY_NUMBER_6,
	KEY_NUMBER_7,
	KEY_NUMBER_8,
	KEY_NUMBER_9,
	KEY_RED,
	KEY_GREEN,
	KEY_YELLOW,
	KEY_BLUE,
	KEY_WHITE,

	KEY_INFO							= 0x40,
	KEY_EPG,
	KEY_SAT,
	KEY_OPTION,
	KEY_FAV,							/* Ferguson Only	*/
	KEY_TELETEXT,						/* IBOX Only		*/

	/* alias */
#ifndef SUPPORT_IBOX_REMOTE
	KEY_AUDIO,
	KEY_SUBTITLE,
#else
	KEY_AUDIO							= KEY_GREEN,
	KEY_SUBTITLE						= KEY_YELLOW,
#endif


	KEY_REW		   						= 0X50,
	KEY_PLAY,
	KEY_STOP,
	KEY_FF,
	KEY_USB,
	KEY_PAUSE,
	KEY_REC,
	KEY_LIVE,


	/* GENIX_NEC_MAP[]		*/
	KEY_GENIX_NOW_NEXT					= 0x70,
	KEY_GENIX_ZOOM,
	KEY_GENIX_FREEZE,
	KEY_GENIX_SLEEP,
	KEY_GENIX_CHLIST,
	KEY_GENIX_DOWNMIX,

	/* DONGWON_NEC_MAP[]	*/


	/* FERGUSON_NEC_MAP[]	*/
	KEY_FERGUSON_USB					= 0x90,
	KEY_FERGUSON_PLAY,
	KEY_FERGUSON_STOP,
	KEY_FERGUSON_PAUSE,
	KEY_FERGUSON_REW,
	KEY_FERGUSON_FF,
	KEY_FERGUSON_REC,

	KEY_QFIND							= 0xA0,
	KEY_ALL_BOUQUET,
	KEY_NETWORK_BOUQUET,
	KEY_PACKAGE_BOUQUET,
	KEY_PROVIDER_BOUQUET,


	/* keys after this line are control */
	KEY_JUMP							= 0xC0,

	/* key codes for local assign */
	KEY_LOCAL_START						= 0xF0,

	/* Unassigned key */
	KEY_CODE_INVALID					= 0xFF,

} key_code_t;


typedef enum
{
	BLIT_MODE_COPY			= 0,
	BLIT_MODE_BLEND			= 0x01,
	BLIT_MODE_TRIG			= 0x10,
	BLIT_DELETE_SOURCE		= 0x20,
	BLIT_MODE_TRIG_X		= 0x40,
	BLIT_MODE_UNDEFINED		= 0x80,
	
} blit_mode_t;



typedef struct widget_s				widget_t;
//typedef struct listbox_s			listbox_t;
//typedef struct scroll_s				scroll_t;
//typedef struct progress_s			progress_t;
//typedef struct label_s				label_t;

typedef struct
{
	unsigned				visible		: 1;
	unsigned				focused		: 1;
	unsigned				dirty		: 1;
} widget_flags_t;

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

typedef struct
{
	unsigned				popup		: 1;
	unsigned				effect		: 1;
	unsigned				blend		: 1;	/* blend background, not copy */
	unsigned				phantom		: 1;	/* just for docking */
} widget_attribute_t;

typedef void				(*widget_draw_func_t)(widget_t *, int *, gfx_rectangle_t *, int);


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
	U16						l;
	U16						r;
	U16						t;
	U16						b;
} gfx_padding_t;


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


typedef struct widget_params_s
{
	/* _WIDGET_PARAMS_STRUCT_  */
	
	gfx_align_t				align;						
	gfx_rectangle_t			rect;						
	gfx_padding_t			pad;						
	widget_attribute_t		attribute;					
	//gfx_bitmap_t			*target;					
	blit_source_t *target;
	blit_source_t			background;					
	blit_source_t			cover;
	char name[20];
	/*------*/
	U32 label_color;
	char *label_text;
	
	
} widget_params_t;
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



typedef struct
{
	//STGXOBJ_Bitmap_t				bitmap;
	blit_source_t bitmap;
	//STAVMEM_BlockHandle_t			block_handle;
	blit_source_t block_handle;
} gfx_surface_buffer_t;

typedef struct gfx_surface_s			gfx_surface_t;

struct gfx_surface_s
{
	void							(*destructor)(gfx_surface_t *thiz);

	//mutex_t							*lock;
	gfx_surface_buffer_t			*front_buffer;
	gfx_surface_buffer_t			*back_buffer;
	gfx_surface_buffer_t			*active_buffer;
	unsigned int								width;
	unsigned int								height;
	//gfx_viewport_t					*viewport;

	struct
	{
		gfx_rectangle_t					granted;	/* clipped by parent on creation */
		gfx_rectangle_t					current;	/* currently available area */
	} area;

	gfx_surface_buffer_t			buffer[2];
};

#define WIDGET_VISIBLE(o)				((o)->widget).flags.visible
#define WIDGET_OF(o)					((o)?&(o)->widget:NULL)
#define WIDGET_DIRTY(o)					((o)->widget).flags.dirty


struct widget_s
{
	dlink_t					dlink;
	widget_t				*parent;
	//gfx_bitmap_t			*target;
	int *target;
	widget_attribute_t		attribute;
	widget_flags_t			flags;

	gfx_rectangle_t			rect;
	gfx_rectangle_t			client; /* client.x=pad.l, client.y=pad.r,client.w=rect.w-pad.l-pad.r,client.h=rect.h-pad.t-pad.b  */

	blit_source_t			background;
	blit_source_t			cover;
	gfx_surface_t			*buffer;
	//gfx_bitmap_t			*capture;
	blit_source_t *capture;
	struct
	{
		size_t				count;
		dlink_list_t		list;
	} children;
	struct
	{
		widget_draw_func_t		draw;
	} custom;
	char name[30];
	/* ---- */
	char label_text[30];
	U32 label_color;
};

typedef struct
{
	widget_t							widget;
	struct { widget_t widget; } 		l, m, r;

} widget_plate_t;
typedef struct
{
	widget_plate_t						_top, _bot;
	struct { widget_t widget; } 		l, r;
} widget_border_t;

#if 0
struct label_s
{
	widget_t				widget;  
	/*   application can use below object  but api use only above widget object : address of "widget" == address of "label variable" */
	U32 label_color;
 	/*
 		just copy const address which address is initial setting value..ie..const char....through  initial struct member value   .text="abcd" 
		so no need array like char label_text[32];
	*/	
	char *label_text;  
	//gfx_pen_t				pen;
	//const char				*text;
	//const char				*remain;
};
typedef struct label_s				label_t;
#endif

extern blit_source_t 							out_border_list[8] ;
extern blit_source_t 						in_border_list[8] ;

/* macros --------------------------------------------------------------------- */



/* variables ------------------------------------------------------------------ */


/* functions ------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
#endif /* __GxLIB_GFX__WIDGET_TYPES_H_ */
/* end of file ---------------------------------------------------------------- */
