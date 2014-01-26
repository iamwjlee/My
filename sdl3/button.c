


/* includes ------------------------------------------------------------------- */
#include "button.h"


/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */


/* macros --------------------------------------------------------------------- */
#define button_from(w)					((button_t*)(w))


/* global variables ----------------------------------------------------------- */


/* local variables ------------------------------------------------------------ */
static button_style_t					default_style =
										{
	//										.pen[0].forecolor.value = 0x80588692,
	//										.pen[1].forecolor.value	= 0x80FFFFFF,
	//										.pen[1].forecolor.value	= 0x80C0C0C0,
											.base[0]				= 0x80c0ede8,
											.base[1]				= 0x8018b3eb,
											.base[1]				= 0x80c0ede8,
										};


/* local function prototypes -------------------------------------------------- */
static void button_draw(widget_t *widget, /*gfx_bitmap_t*/int *target, gfx_rectangle_t *granted, int recursive);


/* global functions ----------------------------------------------------------- */
button_t *button_create(widget_t *parent, button_params_t *params)
{
	button_t				*button = null;

	//if(!default_style.pen[0].font)
	{
		//default_style.pen[0].font = gfx.default_font;
		//default_style.pen[1].font = gfx.default_font;
	}

	if(params)
	{
		button = calloc(1, sizeof(button_t));
		if(button)
		{
			widget_init(WIDGET_OF(button), &params->widget, parent);

			if(!params->style)	params->style = &default_style;
			memcpy(&button->style, params->style, sizeof(button_style_t));
			button->text = params->text;

			WIDGET_OF(button)->custom.draw = button_draw;
			WIDGET_VISIBLE(button) = true;
		}
	}
	return(button);
}

button_t *button_delete(button_t *button)
{
	if(button)
		free(button);
	return(null);
}

void button_set_state(button_t *button, button_state_t state)
{
	if(button)
	{
		button->state = state;
		WIDGET_DIRTY(button) = true;
	}
}

void button_set_text(button_t *button, const char *text)
{
	if(button)
	{
		button->text = text;
		WIDGET_DIRTY(button) = true;
	}
}

/* local functions ------------------------------------------------------------ */
static void button_draw(widget_t *widget, /*gfx_bitmap_t*/int *target, gfx_rectangle_t *granted, int recursive)
{
	button_t				*button		= button_from(widget);
	gfx_pen_t				*pen		= &button->style.pen[button->state];
	blit_source_t			background	= button->style.base[button->state];
	gfx_rectangle_t			client		= widget->client;

	print("button_draw : client[%d-%d-%d-%d] granted[%d-%d-%d-%d]0x%x\n ",
	client.x, client.y,client.w,client.h,  granted->x,granted->y,granted->w,granted->h,widget->background);

	client.x += granted->x;
	client.y += granted->y;


	if(WIDGET_OF(button)->attribute.blend)
		gfx_blit_fill(BLIT_MODE_BLEND,  granted, &background, null);
	else	gfx_blit_fill(BLIT_MODE_COPY,  granted, &background, null);

	//gfx_pen_set_target(pen, target, &client);
	//gfx_new_puts(pen, button->text);
	
 	gfx_blit_label(0,button->text,&client,pen->forecolor);
}


/* shell functions ------------------------------------------------------------ */


/* end of file ---------------------------------------------------------------- */
