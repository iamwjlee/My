#ifndef __LISTBOX_H_
#define __LISTBOX_H_

/* includes ------------------------------------------------------------------- */

#include "scroll.h"
#include "ui.h"

#ifdef __cplusplus
extern "C" {
#endif

/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */
typedef void				(*listbox_draw_item_t)(ui_data_t *, int*, gfx_pen_t*, gfx_rectangle_t *);

typedef struct
{
	gfx_padding_t			pad;
	gfx_pen_t				pen[3];
	blit_source_t			base[3];
	blit_source_t			cover[3];
	scroll_params_t			scroll;
	widget_params_t			spacer;
} listbox_style_t;

typedef struct
{
	widget_params_t			widget;
	U8						lines;
	listbox_style_t			*style;
} listbox_params_t;

struct listbox_s
{
	widget_t				widget;
	//semaphore_t				*lock;
	scroll_t				*scroll;
	ui_datalist_t			*data;

	struct
	{
		gfx_padding_t			pad;
		U8						lines;
		U16						height;
		gfx_pen_t				pen[3];
		blit_source_t			base[3];
		blit_source_t			cover[3];
		ui_data_t				*top;
		listbox_draw_item_t		draw;
//		void					(*draw)(ui_data_t *, gfx_bitmap_t*, gfx_pen_t*, gfx_rectangle_t *);
	} item;
};
typedef struct listbox_s			listbox_t;


/* macros --------------------------------------------------------------------- */


/* variables ------------------------------------------------------------------ */


/* functions ------------------------------------------------------------------ */
extern listbox_t *listbox_create(widget_t *parent, listbox_params_t *params);
extern void listbox_delete(listbox_t *listbox);
extern ui_data_t *listbox_select(listbox_t *listbox, void *object, BOOL page);
extern void listbox_set_datalist(listbox_t *listbox, ui_datalist_t *data);

#if 0
extern void listbox_refresh(listbox_t *listbox);
extern void listbox_set_list(listbox_t *listbox, ui_datalist_t *list);
extern void listbox_select_prev(listbox_t *listbox);
extern void listbox_select_next(listbox_t *listbox);
extern void listbox_select_prev_page(listbox_t *listbox);
extern void listbox_select_next_page(listbox_t *listbox);
#endif


#ifdef __cplusplus
}
#endif
#endif /* __LISTBOX_H_ */
/* end of file ---------------------------------------------------------------- */

