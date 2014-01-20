/********************************************************************************/
/*																				*/
/* File name:	menuitem.h														*/
/*																				*/
/* Description:	Menu Item Interface												*/
/*																				*/
/*																				*/
/* COPYRIGHT (C) Genix InfoComm 2007											*/
/*																				*/
/* Date			Modification									Name			*/
/* ----			------------									----			*/
/* 2007-08-16	Created											MY				*/
/*																				*/
/********************************************************************************/
#ifndef __MENUITEM_H_
#define __MENUITEM_H_

#include "widget.h"
#include"dlink.h"
#include "slink.h"

#ifdef __cplusplus
extern "C" {
#endif

/* constants ------------------------------------------------------------------ */
#define MENUITEM_HEIGHT					60
#define MENUITEM_NORMAL_BACKCOLOR		0x800096c8
#define MENUITEM_SELECTED_BACKCOLOR		0x80c9e55e


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */

typedef struct menuitem_s				menuitem_t;

typedef struct menu_s					menu_t;


//typedef void				(*menuitem_xdraw_t)(menuitem_t *, gfx_bitmap_t *, gfx_rectangle_t *);
//typedef int					(*key_process_t)(menuitem_t *item, ui_message_t *input);













#define _MENU_STRUCT_													\
	slink_t					slink;										\
	menu_t					*parent;									\
	const char				*name;										\
	//event_driver_t			*event;										\
	widget_t				widget;										\
	widget_border_t			border;										\
	widget_t				body;										\
	U32						level;										\
	//menu_help_t				*help;										\
	//menu_view_type_t		view_type;									\
	//label_t					*path;										\
	char					path_string[128];							\
	int						(*run)(menu_t *, menuitem_t *);				\
	struct																\
	{																	\
		size_t				count;										\
		dlink_list_t		list;										\
		menuitem_t			*current;									\
	} item;																\
	widget_t				body2;			/*wj test */						\
	U32						dummy;

struct menu_s
{
	slink_t					slink;										
	menu_t					*parent;								
	const char				*name;										
	//event_driver_t			*event;										
	widget_t				widget;										
	widget_border_t			border;										
	widget_t				body;										
	U32						level;										
	//menu_help_t				*help;										
	//menu_view_type_t		view_type;									
	//label_t					*path;										
	char					path_string[128];							
	int						(*run)(menu_t *, menuitem_t *);				
	struct																
	{																	
		size_t				count;										
		dlink_list_t		list;										
		menuitem_t			*current;									
	} item;																
	widget_t				body2;			/*wj test */					
	U32						dummy;
};





struct menuitem_help_s
{
	U16						line;
	//help_icon_t				*icons;
};

#define _MENUITEM_STRUCT_								\
	dlink_t					dlink;						\
	menu_t					*menu;						\
	struct												\
	{													\
		unsigned			index			: 8;		\
		unsigned			selected		: 1;		\
		unsigned			disabled		: 1;		\
		unsigned			unselectable	: 1;		\
		unsigned			checkable		: 1;		\
		unsigned			checked			: 1;		\
		unsigned			suppress_dialog	: 1;		\
		unsigned			data_locked		: 1;		\
		unsigned			multi			: 1;		\
		unsigned			reserved		: 16;		\
	};													\
														\
	const char				*name;						\
	const char				*caption;					\
	const char				*shortcut;					\
	widget_t				widget;						\
	//ui_datalist_t			data;						\
	gfx_rectangle_t			data_rect;					\
	gfx_rectangle_t			data_client;				\
	//menuitem_xdraw_t		draw_help;					\
	//menuitem_help_t			help;


struct menuitem_s
{
	_MENUITEM_STRUCT_
};

typedef enum
{
	MENU_LEVEL_DEFAULT,

	MENU_LEVEL_MAIN,

	MENU_LEVEL_CHANNEL_EDIT		= 5,
	MENU_LEVEL_CH_SELECT,
	MENU_LEVEL_SIMPLE,

	MENU_LEVEL_SHORT			= 0x80,
	MENU_LEVEL_CH_SORT,
	MENU_LEVEL_USB,
} menu_level_t;


/* macros --------------------------------------------------------------------- */


/* variables ------------------------------------------------------------------ */



/* functions ------------------------------------------------------------------ */
extern menuitem_t *menuitem_new(menu_t *menu, const char *name, const char *caption, const char *shortcut);
extern menuitem_t *menuitem_init(menuitem_t *item, menu_t *menu, const char *name, const char *caption, const char *shortcut);
extern menuitem_t *dialog_menuitem_new(widget_t *parent, const char *name, const char *caption, const char *shortcut);
extern void menuitem_purge_data(menuitem_t *item);
//extern void menuitem_add_data(menuitem_t *item, ui_data_t *data);
extern void menuitem_select_data(menuitem_t *item, void *object);
extern void menuitem_set_datalist(menuitem_t *item, dlink_list_t list);
extern void menuitem_modify_data(menuitem_t *item, void *object);


extern void menuitem_disable(menuitem_t *item);
extern void menuitem_enable(menuitem_t *item);
extern void menuitem_select(menuitem_t *item);
extern void menuitem_deselect(menuitem_t *item);
extern menuitem_t *menuitem_from(widget_t *widget);

/* for extension */
//extern void _menuitem_draw_caption(menuitem_t *item, gfx_bitmap_t *target, gfx_rectangle_t *granted);
//extern void _menuitem_draw_data(menuitem_t *item, gfx_bitmap_t *target, gfx_rectangle_t *granted);







#ifdef __cplusplus
}
#endif
#endif /* __MENUITEM_H_ */
/* end of file ---------------------------------------------------------------- */

