
/* includes ------------------------------------------------------------------- */
#include "my_sdl.h"
#include "dlink.h"
#include "ui.h"

/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */



/* macros --------------------------------------------------------------------- */
#define IS_SELECTABLE_DATUM(d)			(!(d)->disabled)


/* local function prototypes -------------------------------------------------- */



/* global variables ----------------------------------------------------------- */
U8										ui_data_const_none;
U8										ui_data_const_first;
U8										ui_data_const_last;
U8										ui_data_const_next;
U8										ui_data_const_prev;
U8										ui_data_const_current;

#define UI_DATUM_ENABLE(d)				(d)->disabled = false
#define UI_DATUM_DISABLE(d)				(d)->disabled = true


/* local variables ------------------------------------------------------------ */


/* global functions ----------------------------------------------------------- */



BOOL ui_datalist_init(ui_datalist_t *datalist)
{
	if(datalist)
	{
		memset(datalist, 0, sizeof(ui_datalist_t));
		//datalist->lock = mutex_create_fifo();
		return(false);
	}
	return(true);
}

ui_datalist_t *ui_datalist_new(void)
{
	ui_datalist_t			*datalist = calloc(1, sizeof(ui_datalist_t));

	if(datalist)
	{
		//datalist->lock = mutex_create_fifo();
	}
	return(datalist);
}

void ui_datalist_set_list(ui_datalist_t *datalist, dlink_list_t list)
{
	if(datalist)
	{
		ui_data_t				*data;

		//mutex_lock(datalist->lock);

		datalist->count		= 0;
		datalist->current	= (ui_data_t *)list;

		dlink_foreach(data, list)
			data->index	= datalist->count++;

		datalist->list = list;
		//mutex_release(datalist->lock);
	}
}

void ui_datalist_sort(ui_datalist_t *datalist, dlink_comparator compare)
{
	if(datalist && compare)
	{
		ui_data_t				*data;

		dlink_sort(datalist->list, compare);
		datalist->count = 0;
		dlink_foreach(data, datalist->list)
			data->index	= datalist->count++;
	}
}

void ui_datalist_clear(ui_datalist_t *datalist)
{
	if(datalist)
	{
		ui_data_t				*datum, *safe;

		//mutex_lock(datalist->lock);
		dlink_foreach_safe(datum, safe, datalist->list)
			free(datum);
		datalist->list		= null;
		datalist->count		= 0;
		datalist->current	= null;
		//mutex_release(datalist->lock);
	}
}

void ui_datalist_purge(ui_datalist_t *datalist)
{
	if(datalist)
	{
		ui_data_t				*datum, *safe;

		//mutex_lock(datalist->lock);
		datalist->list		= null;
		datalist->count		= 0;
		datalist->current	= null;
		//mutex_release(datalist->lock);
	}
}

void ui_datalist_add(ui_datalist_t *datalist, ui_data_t *data)
{
	if(datalist && data)
	{
		//mutex_lock(datalist->lock);

		if(!datalist->current)
		{
			datalist->current = data;
			data->selected = true;
		}
		else	data->selected = false;
		data->index	= datalist->count++;
		dlink_append(datalist->list, data);
		//mutex_release(datalist->lock);
	}
}


void ui_datalist_remove(ui_datalist_t *datalist, ui_data_t *data)
{
	if(datalist && data)
	{
		ui_data_t				*elem;

		//mutex_lock(datalist->lock);

		if(datalist->current == data)
		{
			if(dlink_next_of(data))
			{
				datalist->current = dlink_next_of(data);
				datalist->current->selected = true;
			}
			else if(dlink_prev_of(data) != data)	/* data != last_of_list */
			{
				datalist->current = (ui_data_t *)data->dlink.prev;
				datalist->current->selected = true;
			}
			else	datalist->current = null;
		}

		for(elem = (ui_data_t *)data->dlink.next; elem != null; elem = (ui_data_t *)elem->dlink.next)
			elem->index = elem->index - 1;

		if(datalist->count)	datalist->count--;
		dlink_remove(datalist->list, data);
		free(data);

		//mutex_release(datalist->lock);
	}
}

void ui_datalist_remove_object(ui_datalist_t *datalist, void *object)
{
	ui_data_t				*data = null;

	if(datalist)
	{
		//mutex_lock(datalist->lock);
		dlink_foreach(data, datalist->list)
			if(data->object == object)
				break;
		//mutex_release(datalist->lock);

		ui_datalist_remove(datalist, data);
	}
}


ui_data_t *ui_datalist_select(ui_datalist_t *data, void *object)
{
	if(data)
	{
		//mutex_lock(data->lock);
		if(data->current)
			data->current->selected = false;

		if(object == UI_DATA_NONE)
		{
			data->current = null;
		}
		else if(object == UI_DATA_FIRST)
		{
			dlink_foreach(data->current, data->list)
				if(IS_SELECTABLE_DATUM(data->current))
					break;
		}
		else if(object == UI_DATA_LAST)
		{
			data->current = dlink_last_of(data->list);
			while(data->current)
			{
				if(IS_SELECTABLE_DATUM(data->current))
					break;
				if(data->current == (ui_data_t *)data->list)
				{
					data->current = null;
					break;
				}
				data->current = dlink_prev_of(data->current);
			}
		}
		else if(object == UI_DATA_NEXT)
		{
			ui_data_t				*next = null;

			if(data->current)
				next = dlink_next_of(data->current);
			if(!next)	next = (ui_data_t*)data->list;

			while(next != data->current)
			{
				if(IS_SELECTABLE_DATUM(next))
				{
					data->current = next;
					break;
				}

				next = dlink_next_of(next);
				if(!next && data->current)
					next = (ui_data_t *)data->list;
			}
		}
		else if(object == UI_DATA_PREV)
		{
			ui_data_t				*prev = null;

			if(data->current)
				prev = dlink_prev_of(data->current);
			else	data->current = prev = dlink_last_of(data->list);

			do
			{
				if(IS_SELECTABLE_DATUM(prev))
				{
					data->current = prev;
					break;
				}
				prev = dlink_prev_of(prev);
			} while(prev != data->current);

			if(!IS_SELECTABLE_DATUM(data->current))
				data->current = null;
		}
		else if(object != UI_DATA_CURRENT)
		{
			ui_data_t				*datum;

			dlink_foreach(datum, data->list)
				if((datum == object) || (datum->object == object))
					break;
			data->current = datum;
		}

		if(data->current)
			data->current->selected = true;
		//mutex_release(data->lock);
		return(data->current);
	}
	return(null);
}

ui_data_t *ui_data_new(const char *caption, void *object)
{
	ui_data_t				*data = null;

	data = calloc(1, sizeof(ui_data_t));
	if(data)
	{
		data->object	= object;
		data->caption	= caption;
	}
	return(data);
}

ui_data_t *ui_data_new_embedded_caption(const char *caption, void *object)
{
	ui_data_t				*data = calloc(1, sizeof(ui_data_t) + strlen(caption));

	if(data)
	{
		strcpy(data->caption_buffer, caption);

		data->object	= object;
		data->caption	= data->caption_buffer;
	}
	return(data);
}

ui_data_t *ui_data_search_by_object(ui_datalist_t *datalist, void *object)
{
	ui_data_t				*data = null;

	if(datalist)
	{
		dlink_foreach(data, datalist->list)
			if(data->object == object)
				break;
	}
	return(data);
}

void ui_datum_draw(ui_data_t *datum, gfx_pen_t *pen)
{
	if(datum && pen)
	{
		//gfx_new_puts(pen, datum->caption);
		print(" Not yet------------\n");
	}	
}


/* local functions ------------------------------------------------------------ */
#if 0
void ui_data_print_caption(gfx_pen_t *pen, ui_data_t *data)
{
	if(data->flag & UI_ITEM_FLAG_CAPTION_FUNCTION)
	{
#if 0
		U32						temp = (U32)data->caption;
		ui_data_get_caption_t	*get_caption = (ui_data_get_caption_t *)temp;

		caption = get_caption(data);
		caption = ((ui_data_get_caption_t *)data->caption)(data);
#endif
	}
	else
	{
		gfx_new_puts(pen, data->caption);
	}
}

ui_data_t *ui_data_get_next_valid(ui_datalist_t *datalist)
{
	ui_data_t				*next = null;

	if(datalist && datalist->list)
	{
		if(datalist->current)
			next = dlink_next_of((ui_data_t *)datalist->current);

		if(next == null)
			next = (ui_data_t *)datalist->list;

		while(next != datalist->current)
		{
			if(IS_SELECTABLE_DATUM(next))
				break;
			next = dlink_next_of(next);
			if(!next)
			{
				if(datalist->current)	next = (ui_data_t *)datalist->list;
				else					break;
			}
		}
	}
	return(next);
}

ui_data_t *ui_data_get_prev_valid(ui_datalist_t *datalist)
{
	ui_data_t				*prev = null;

	if(datalist && datalist->list)
	{
		if(datalist->current)	prev = dlink_prev_of((ui_data_t *)datalist->current);
		else					prev = dlink_prev_of((ui_data_t *)datalist->list);

		while(prev != datalist->current)
		{
			if(IS_SELECTABLE_DATUM(prev))
				break;
			prev = dlink_prev_of(prev);
			if(prev == dlink_prev_of((ui_data_t *)datalist->list))
				if(!datalist->current)
					break;
		}
	}
	return(prev);
}
#endif

ui_datalist_t 		mydatalist;

int  datalist_test(void)
{

	ui_datalist_t 		*datalist = &mydatalist;
	//listbox_t 			list;
	ui_data_t 			*data;

	ui_datalist_init(datalist);
	data = ui_data_new("a1", (void *)1);
	ui_datalist_add(datalist, data);


	data = ui_data_new("a2", (void *)2);
	ui_datalist_add(datalist, data);

	data = ui_data_new("a3", (void *)3);
	ui_datalist_add(datalist, data);
	
	ui_datalist_select(datalist, UI_DATA_FIRST);
	{
		
		ui_data_t 			*datum;
		dlink_foreach(datum, datalist->list)
		{
			print(" %s - %d\r\n",datum->caption,(int)datum->object);

		}
		
	}

}


/* end of file ---------------------------------------------------------------- */
