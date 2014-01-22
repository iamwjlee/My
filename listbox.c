

/* includes ------------------------------------------------------------------- */
#include "my_sdl.h"
#include "dlink.h"
#include "ui.h"
#include "listbox.h"

/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */


/* macros --------------------------------------------------------------------- */
#define listbox_from(w)					((listbox_t*)(w))
#define LOCK(l)							//semaphore_wait((l)->lock)
#define UNLOCK(l)						//semaphore_signal((l)->lock)


/* global variables ----------------------------------------------------------- */


/* local variables ------------------------------------------------------------ */
static listbox_style_t					defalut_style =
										{
											.pad						= { 20, 20, 4, 0 },

											.pen[0].forecolor.value		= 0x80588692,
											.pen[1].forecolor.value		= 0x806A4700,
											.pen[2].forecolor.value		= 0x80B3BDBD,

											.base[0]					= 0x80c0ede8,
											.base[1]					= 0x80c9e55e/*0x80D4EB39*/,
											.base[2]					= 0x80d4f5e8,

											.cover[0]					= BLIT_SOURCE_NONE,
											.cover[1]					= BLIT_SOURCE_NONE,
											.cover[2]					= BLIT_SOURCE_NONE,

											.scroll.widget.rect			= { 0, 0, 22, 0 },
											.scroll.widget.pad			= { 2, 3,  0, 0 },
											.scroll.widget.align		= GfxDOCK_RIGHT,
											.scroll.widget.background	= 0x80588692,	/* 0x80588692 */
											.scroll.thumb				= 0x80E8F7F7,	/* 0x801E4E60,*/
											.scroll.cover				= BLIT_SOURCE_NONE,

											.spacer.rect				= { 0, 0, 14, 0 },
											.spacer.align				= GfxDOCK_RIGHT,
										};


/* local function prototypes -------------------------------------------------- */
static void listbox_widget_draw(widget_t *widget, int *target, gfx_rectangle_t *granted, int recursive);


/* global functions ----------------------------------------------------------- */
listbox_t *listbox_create(widget_t *parent, listbox_params_t *params)
{
	listbox_t				*listbox;

	//if(!defalut_style.pen[0].font)
	
	//{
	//	int						i;

	//	for(i = 0 ; i < 3 ; i++)
	//		defalut_style.pen[i].font = gfx.default_font;
	//}

	if(params)
	{
		listbox = calloc(1, sizeof(listbox_t));
		if(listbox)
		{
			if(!widget_init(WIDGET_OF(listbox), &params->widget, parent))
			{
				listbox_style_t			*style = params->style ? params->style : &defalut_style;
				int						i;

				WIDGET_OF(listbox)->custom.draw = listbox_widget_draw;

				//listbox->lock = semaphore_create_fifo(1);
				if(style->scroll.widget.rect.w || style->scroll.widget.rect.h)
					listbox->scroll	= scroll_create(WIDGET_OF(listbox), &style->scroll);
				if(style->spacer.rect.w)
					widget_dock_space(WIDGET_OF(listbox), &style->spacer);

				for(i = 0 ; i < 3 ; i++)
				{
					listbox->item.pen[i]	= style->pen[i];
					listbox->item.base[i]	= style->base[i];
					listbox->item.cover[i]	= style->cover[i];
					///if(!listbox->item.pen[i].font)
					///	listbox->item.pen[i].font = gfx.default_font;
				}
				listbox->item.pad		= style->pad;
				listbox->item.lines		= params->lines;
				listbox->item.height	= WIDGET_OF(listbox)->client.h / listbox->item.lines;
				WIDGET_VISIBLE(listbox) = true;
			}
			else
			{
				free(listbox);
				listbox = null;
			}
		}
	}
	return(listbox);
}

void listbox_delete(listbox_t *listbox)
{
	if(listbox)
	{
		//semaphore_wait(listbox->lock);
		//semaphore_delete(listbox->lock);
		if(listbox->scroll)	free(listbox->scroll);
		free(listbox);
	}
}

void listbox_set_datalist(listbox_t *listbox, ui_datalist_t *data)
{
	if(listbox)
	{
		LOCK(listbox);
		listbox->data = data;
		listbox->item.top = null;
		if(data)
		{
			scroll_config(listbox->scroll,
				data->count * listbox->item.height, listbox->item.lines * listbox->item.height);

			if(!data->current)	data->current = (ui_data_t *)data->list;
		}
		UNLOCK(listbox);
	}
}

ui_data_t *listbox_select(listbox_t *listbox, void *object, BOOL page)
{
	if(listbox && listbox->data && listbox->data->list)
	{
		ui_datalist_t			*data = listbox->data;

		LOCK(listbox);

		if(!page)
		{
			ui_data_t				*top = listbox->item.top;

			data->current = (ui_data_t *)ui_datalist_select(data, object);

			if(data->current)
			{
				if(listbox->item.top)
					top = listbox->item.top;
				else if(data->count <= listbox->item.lines)
					top = (ui_data_t*)data->list;

				else	top = data->current;

				while(data->current->index < top->index)
					top = dlink_prev_of(top);

				while(data->current->index >= (top->index + listbox->item.lines))
					top = dlink_next_of(top);

				while(top->index > (U16)(data->count - listbox->item.lines))
					top = dlink_prev_of(top);

				while(top->index && ((data->count - top->index) < listbox->item.lines))
					top = dlink_prev_of(top);

				listbox->item.top = top;
			}
			else
			{
				data->current = listbox->item.top = (ui_data_t*)data->list;
				data->current->selected = true;
			}
		}
		else
		{
			int						count = listbox->item.lines;

			if(!data->current)
				ui_datalist_select(data, UI_DATA_FIRST);

			if(object == UI_DATA_PREV)
			{
				ui_data_t				*prev_valid = data->current;

				while(prev_valid && dlink_prev_of(prev_valid)->dlink.next)
				{
					prev_valid = dlink_prev_of(prev_valid);
					if(prev_valid && !prev_valid->disabled)
						break;
				}

				if(	(data->current == (ui_data_t *)data->list) &&
					(prev_valid == (ui_data_t *)data->list))
				{
					ui_data_t				*top;

					data->current =(ui_data_t *)ui_datalist_select(data, UI_DATA_LAST);
					DEBUG_ASSERT(data->current);

					top = data->current;
					while(--count && top->index)
						top = dlink_prev_of(top);
					listbox->item.top = top;
				}
				else
				{
					ui_data_t				*top = listbox->item.top;

					if(data->current == top)
						while(top->index && count--)
							top = dlink_prev_of(top);

					while(top && top->disabled && dlink_next_of(top))
						top = dlink_next_of(top);
					listbox->item.top = (ui_data_t *)ui_datalist_select(data, top);
				}
			}
			else if(object == UI_DATA_NEXT)
			{
				ui_data_t				*top		= listbox->item.top;
				ui_data_t				*bottom		= top;
				ui_data_t				*last_object = data->list ? (ui_data_t *)((dlink_t *)data->list)->prev : null;
				ui_data_t				*next_valid = data->current;

				while(next_valid)
				{
					next_valid = dlink_next_of(next_valid);
					if(next_valid && !next_valid->disabled)
						break;
				}

				if(	(data->current == last_object) || !next_valid)
				{
					listbox->item.top = (ui_data_t *)ui_datalist_select(data, UI_DATA_FIRST);
				}
				else
				{
					while(--count && dlink_next_of(bottom))
						bottom = dlink_next_of(bottom);

					if(data->current == bottom)
					{
						count = listbox->item.lines;
						while(count-- && dlink_next_of(bottom))
							bottom = dlink_next_of(bottom);
					}

					while(bottom && bottom->disabled && (dlink_prev_of(bottom) != last_object))
						bottom = dlink_prev_of(bottom);
					ui_datalist_select(data, bottom);

					top = data->current;
					count = listbox->item.lines;

					while(--count && top->index)
						top = dlink_prev_of(top);
					listbox->item.top = top;
				}
			}
			else
			{
				DEBUG_ASSERT((object == UI_DATA_PREV) || (object == UI_DATA_NEXT));
			}
		}
		if(WIDGET_OF(listbox)->flags.visible)
		{
			//flip_start();
			widget_show(WIDGET_OF(listbox), true);
			flip_end(false);
		}
		else	WIDGET_DIRTY(listbox) = true;
		UNLOCK(listbox);
		return(listbox->data->current);
	}
	return(null);
}


/* local functions ------------------------------------------------------------ */
gfx_rectangle_t gfx_rectangle_padded(gfx_rectangle_t *ref, gfx_padding_t *pad)
{
	gfx_rectangle_t			padded;

	padded.x = pad->l;
	padded.y = pad->t;
	padded.w = ref->w - (pad->l + pad->r);
	padded.h = ref->h - (pad->t + pad->b);
	return(padded);
}

static void listbox_widget_draw(widget_t *widget, int *target, gfx_rectangle_t *granted, int recursive)
{
	listbox_t				*listbox = listbox_from(widget);
	ui_datalist_t			*data = listbox->data;

	if(data && data->count)
	{
		gfx_rectangle_t			client = widget->client;
		size_t					count = 0;
		ui_data_t				*datum;

		client.x += granted->x;
		client.y += granted->y;
		client.h = listbox->item.height;

		dlink_foreach(datum, listbox->item.top)
		{
			int						state = datum->disabled ? 2 : datum->selected;

			gfx_blit_fill(BLIT_MODE_COPY, target, &client, &listbox->item.base[state], null);
			{
				gfx_pen_t				*pen = &listbox->item.pen[state];
				gfx_rectangle_t			padded = gfx_rectangle_padded(&client, &listbox->item.pad);

				padded.x += client.x;
				padded.y += client.y;
				///gfx_pen_set_target(pen, target, &padded);

				if(listbox->item.draw)	listbox->item.draw(datum, target, pen, &client);
				else					ui_datum_draw(datum, pen);
			}


			gfx_blit_fill(BLIT_MODE_BLEND,  &client, &listbox->item.cover[state], null);

			client.y += listbox->item.height;
			if(++count == listbox->item.lines)
				break;
		}

		if(listbox->scroll)
		{
			scroll_config(listbox->scroll, (data->count * listbox->item.height), (listbox->item.lines * listbox->item.height));
			scroll_set_value(listbox->scroll, listbox->item.top->index * listbox->item.height);
			if(WIDGET_OF(listbox->scroll)->parent != WIDGET_OF(listbox))
				widget_show(WIDGET_OF(listbox->scroll), false);
		}
	}
}


/* end of file ---------------------------------------------------------------- */
