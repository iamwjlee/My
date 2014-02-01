#ifndef _MY_VIEW2_H
#define _MY_VIEW2_H

/* includes ------------------------------------------------------------------- */
#include "my_sdl.h"
#include "q.h"
#include "ui.control.h"


#include "widget.h"
#include"dlink.h"
#include "slink.h"

#include "menuitem.h"

#include "listbox.h"
#include "scroll.h"
#include "button.h"

#include "math.h"
#include "gt.h"

#include "ui.view.h"

#include "dlink.h"

 
#ifdef __cplusplus
extern "C" {
#endif

/* constants ------------------------------------------------------------------ */


/* types ---------------------------------------------------------------------- */

 struct my2_instance_s
 {
	slink_t 				slink;										
	menu_t					*parent;									
	const char				*name;		
	int x;
	widget_t				widget; 								
	widget_border_t 		border; 	
	widget_border_t 	 client;
	widget_t				body; 			
	widget_t				top; 				
	widget_t				bottom;
	
	widget_t				title; //for text
 	gfx_rectangle_t			area;

	//test 	
	widget_t 			 icon;
	widget_t 			 icon_info;
	widget_t 			 icon_yellow;

	//for list
	ui_datalist_t			datalist;
	scroll_t  *scroll;  // scroll first before list
	listbox_t *list;
	//
	struct
	{
		listbox_t				*list;
		scroll_t				*scroll;
		widget_t				left;
		widget_t				right;
		widget_t				top;
		widget_t				bottom;
	} listbox;
	//

	// button
	button_t 			 *button[3];
	int						current;
	//
	
	//U32 					level;									
	//U32 					dummy;
	// widget_t 			 *title;
	
 	//  task_t 				 *task;
 };
typedef struct my2_instance_s	my_instance_t;



/* macros --------------------------------------------------------------------- */



/* variables ------------------------------------------------------------------ */


/* functions ------------------------------------------------------------------ */
int my_view2_init(void);

//extern my_instance_t *my2;

#ifdef __cplusplus
}
#endif
#endif 
/* end of file ---------------------------------------------------------------- */
