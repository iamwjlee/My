/* includes ------------------------------------------------------------------- */
#include "my_sdl.h"
#include "dlink.h"
#include "ui.h"
#include "scroll.h"

/* constants ------------------------------------------------------------------ */
#define SCROLL_THUMB_MIN_SIZE		10

/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */


/* macros --------------------------------------------------------------------- */
#define scroll_from(w)				((scroll_t*)(w))


/* local variables ------------------------------------------------------------ */


/* global variables ----------------------------------------------------------- */


/* local function prototypes -------------------------------------------------- */
static void scroll_widget_draw(widget_t *widget, int *target, gfx_rectangle_t *granted, int recursive);


/* global functions ----------------------------------------------------------- */
scroll_t *scroll_create(widget_t *parent, scroll_params_t *params)
{
	scroll_t				*scroll = calloc(1, sizeof(scroll_t));

	if(scroll)
	{
		widget_init(WIDGET_OF(scroll), (widget_params_t*)params, parent);
		WIDGET_OF(scroll)->custom.draw = scroll_widget_draw;
		//widget_show(WIDGET_OF(scroll), true);

		scroll->cover		= params->cover;
		scroll->thumb		= params->thumb;
		scroll->vertical	= (scroll->widget.rect.h > scroll->widget.rect.w);
		if(scroll->vertical)
			scroll->full = scroll->active = WIDGET_OF(scroll)->client.h;
		else	scroll->full = scroll->active = WIDGET_OF(scroll)->client.w;
	}
	return(scroll);
}

void scroll_set_value(scroll_t *scroll, U32 value)
{
	if(scroll)
	{
		if(value > (scroll->full - scroll->active))
			value = (scroll->full - scroll->active);
		//if(scroll->value != value)
		{
			scroll->value = value;
			WIDGET_DIRTY(scroll) = true;
		}
//		if(WIDGET_OF(scroll)->flags.visible)
//			widget_show(WIDGET_OF(scroll), false);
	}
}

BOOL scroll_config(scroll_t *scroll, U32 full, U32 active)
{
	if(scroll)
	{
		if(active > full)
			active = full;

		if((scroll->full != full) || (scroll->active != active))
		{
			scroll->full	= full;
			scroll->active	= active;
			WIDGET_DIRTY(scroll) = true;
		}
		scroll_set_value(scroll, scroll->value);
	}
	return(false);
}


/* local functions ------------------------------------------------------------ */
static void scroll_widget_draw(widget_t *widget, int *target, gfx_rectangle_t *granted, int recursive)
{
	scroll_t				*scroll	= scroll_from(widget);
	gfx_rectangle_t			thumb	= widget->client;
	U32						full_size, offset, size;

	print33("scroll_widget_draw\n");

	if(scroll->full > scroll->active)
	{
		if(scroll->vertical)
			full_size = widget->client.h;
		else	full_size = widget->client.w;

		size = ((full_size * scroll->active) + (scroll->full - 1)) / scroll->full;
		offset = ((full_size * scroll->value) + (scroll->full - 1)) / scroll->full;

		if(size < SCROLL_THUMB_MIN_SIZE)
			size = SCROLL_THUMB_MIN_SIZE;
		if((offset + size) > full_size)
			offset = full_size - size;

		if(scroll->vertical)
		{
			thumb.h = size;
			thumb.y += offset;
		}
		else
		{
			thumb.w = size;
			thumb.x += offset;
		}
		thumb.x += granted->x;
		thumb.y += granted->y;
		gfx_blit_fill(BLIT_MODE_COPY,  &thumb, &scroll->thumb, null);
	}
	if(scroll->cover)
		gfx_blit_fill(BLIT_MODE_BLEND,  granted, &scroll->cover, null);
}


/* shell functions ------------------------------------------------------------ */


/* end of file ---------------------------------------------------------------- */
