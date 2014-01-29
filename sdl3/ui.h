

#ifndef _UI__H_
#define _UI__H_

#include "my_sdl.h"
#include "widget.h"
#include "slink.h"
//#include "q.h"


#define UI_DATA_NONE					((void*)&ui_data_const_none)
#define UI_DATA_FIRST					((void*)&ui_data_const_first)
#define UI_DATA_LAST					((void*)&ui_data_const_last)
#define UI_DATA_NEXT					((void*)&ui_data_const_next)
#define UI_DATA_PREV					((void*)&ui_data_const_prev)
#define UI_DATA_CURRENT					((void*)&ui_data_const_current)

extern U8								ui_data_const_none;
extern U8								ui_data_const_first;
extern U8								ui_data_const_last;
extern U8								ui_data_const_next;
extern U8								ui_data_const_prev;
extern U8								ui_data_const_current;


typedef struct ui_view_s
{
	slink_t					slink;
	const char				name[24];
	gfx_rectangle_t			area;
	U8						priority;
	unsigned				active		: 1;
	unsigned				visible		: 1;
	unsigned				paused		: 1;
	osclock_t				lifetime;
	osclock_t				expire;
	osclock_t				protect;
	osclock_t				update_time;
//	int						(*init)(struct ui_view_s *);
	int						(*show)(struct ui_view_s *);
	int						(*hide)(struct ui_view_s *);
	int						(*update)(struct ui_view_s *);
	int						(*pause)(struct ui_view_s *);
	int						(*resume)(struct ui_view_s *);
	int						(*ioctl)(struct ui_view_s *, int, void *);
	void					*instance;
} ui_view_t;


typedef enum
{
	UI_ITEM_STATE_NORMAL				= 0x00,
	UI_ITEM_STATE_SELECTED				= 0x01,
	UI_ITEM_STATE_DISABLED				= 0x02,
	UI_ITEM_STATE_COUNT,
} ui_item_state_t;




struct ui_data_s
{
	dlink_t					dlink;											
	U16						index;												
	unsigned				disabled	: 1;								
	unsigned				selected	: 1;									
	unsigned				checked		: 1;									
	unsigned				checkable	: 1;								
	unsigned				empty		: 1;								
	unsigned				reserved	:11;
	void					*object;
	const char				*caption;
	char					caption_buffer[4];
};
typedef struct ui_data_s				ui_data_t;


struct ui_datalist_s
{
	//mutex_t					*lock;
	void					*owner;
	size_t					count;
	dlink_list_t			list;
	ui_data_t				*current;
};

typedef struct ui_datalist_s			ui_datalist_t;


/* ui_data.c */
extern BOOL ui_datalist_init(ui_datalist_t *datalist);
extern ui_datalist_t *ui_datalist_new(void);
extern void ui_datalist_set_list(ui_datalist_t *datalist, dlink_list_t list);
extern void ui_datalist_sort(ui_datalist_t *datalist, dlink_comparator compare);
extern void ui_datalist_clear(ui_datalist_t *datalist);		/* free data */
extern void ui_datalist_purge(ui_datalist_t *datalist);
extern void ui_datalist_add(ui_datalist_t *datalist, ui_data_t *data);
extern void ui_datalist_remove(ui_datalist_t *datalist, ui_data_t *data);
extern void ui_datalist_remove_object(ui_datalist_t *datalist, void *object);
extern ui_data_t *ui_datalist_select(ui_datalist_t *datalist, void *object);
extern ui_data_t *ui_data_new(const char *caption, void *object);
extern ui_data_t *ui_data_new_embedded_caption(const char *caption, void *object);
extern ui_data_t *ui_data_search_by_object(ui_datalist_t *datalist, void *object);
extern void ui_datum_draw(ui_data_t *datum, gfx_pen_t *pen);


#endif
