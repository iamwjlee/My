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
 
#define d_print(...)  dprint(__VA_ARGS__)
 

// -----------------------------------------------------




 typedef struct
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
 } my_instance_t;

static my_instance_t				 menu_instance;

 blit_source_t							 out_border_list[8] =
										 {
											 (blit_source_t )DATADIR"border.out.NW.png",
											 (blit_source_t )DATADIR"border.out.NE.png",
											 (blit_source_t )DATADIR"border.out.N.png",
											 (blit_source_t )DATADIR"border.out.SW.png",
											 (blit_source_t )DATADIR"border.out.SE.png",
											 (blit_source_t )DATADIR"border.out.S.png",
											 (blit_source_t )DATADIR"border.out.W.png",
											 (blit_source_t )DATADIR"border.out.E.png",
										 };
 
 blit_source_t						 in_border_list[8] =
										 {
											 (blit_source_t)DATADIR"border.in.NW.png",
											 (blit_source_t)DATADIR"border.in.NE.png",
											 (blit_source_t)DATADIR"border.in.N.png",
											 (blit_source_t)DATADIR"border.in.SW.png",
											 (blit_source_t)DATADIR"border.in.SE.png",
											 (blit_source_t)DATADIR"border.in.S.png",
											 (blit_source_t)DATADIR"border.in.W.png",
											 (blit_source_t)DATADIR"border.in.E.png",
										 };

 static listbox_style_t 				 service_list_style =
										 {
											 .pad = { 10, 40, 4, 0 },
 
											 .pen[0].forecolor.value	 = 0x800070A0,
											 .pen[0].align			 = GfxALIGN_LEFT,
											 .pen[1].forecolor.value	 = 0x806A4700,
											 .pen[1].align			 = GfxALIGN_LEFT,
											 .pen[2].forecolor.value	 = 0x80B2B2B2,
											 .pen[2].align			 = GfxALIGN_LEFT,
 
											 .base[0] 				 = 0x80C0F0F0, //0x80c0ede8, background of list text!
											 .base[1] 				 = 0x80c9e55e,
											 .base[2] 				 = 0x80d4f5e8,
 
											 .cover[0]				 = BLIT_SOURCE_NONE,
											 .cover[1]				 = BLIT_SOURCE_NONE,
											 .cover[2]				 = BLIT_SOURCE_NONE,
										 };

 static void label_custom_draw(widget_t *widget, int *target, gfx_rectangle_t *granted, int recursive)
 {
	// label_t				 *label  = label_from(widget);
	 //gfx_pen_t				 *pen	 = &label->pen;
	 gfx_rectangle_t		 client  = widget->client;
	gfx_color_t color;
 
  	d_print("label_custom_draw : client[%d-%d-%d-%d] granted[%d-%d-%d-%d]   [%s] ",
 	client.x, client.y,client.w,client.h,  granted->x,granted->y,granted->w,granted->h,widget->label_text);
 
	 client.x += granted->x;
	 client.y += granted->y;
	 

	//gfx_blit_label(&client,widget->background);
	//strcpy(text,"Good");
	color.value= widget->label_color;
	gfx_blit_label(0,widget->label_text,&client,color);


	
	// gfx_pen_set_target(pen, target, &client);
	 //label->remain = gfx_new_puts(pen, label->text);
	 
 }
 static void draw_service_item(ui_data_t *datum, int *target, gfx_pen_t *pen, gfx_rectangle_t *client)
 {
 	
	if(*datum->caption)
	{
		gfx_rectangle_t r;
	 	print32("x[%03d] y[%03d] w[%03d] h[%03d] color[0x%x]",client->x,client->y,client->w,client->h,(unsigned int)pen->forecolor.value);
		print32("draw_service_item [%s]",datum->caption);
			
		pen->area.granted =*client;
		r=pen->area.granted;
		
		print32("pen [%03d-%03d-%03d-%03d]",r.x,r.y,r.w,r.h);
		gfx_new_puts(pen,datum->caption);
		if(0){
			gfx_rectangle_t  rec;
			rec.x=client->x;
			rec.y=client->y;
			rec.w=client->w;
			rec.h=client->h;
			
		gfx_blit_label(0, "safffa",&rec,GFX_COLOR(0x80ff0000));
		
		SDL_Flip( screen );
		}
	}
 }

 int my_view_layout(my_instance_t *menu)
{
	
	widget_params_t base	= { .rect = { 160, 10, 500, 580 },  .attribute.popup = 1, .background =	0, .name="my.view.base"};
 
 	widget_params_t top  = { .label_text="love", .label_color=LABEL_COLOR,
		.rect = { 0, 0, 0, 40 },	.align = GfxDOCK_TOP, .background =  BODY_COLOR, .name="my.view.top" };
  	widget_params_t help  = { .rect = { 0, 0, 0, 80},  .pad = { 0, 0, 2, 0},  .align = GfxDOCK_BOTTOM,.background = BODY_COLOR,.name="my.view.help" };
	widget_params_t body	= { .rect = { 0, 0,  0, 0 },			.align = GfxDOCK_FILL,	.background = CLIENT_BODY,.name="my.view.body" };

	/* 
	
	what's blend  mode ?		it need 

	*/

	
widget_params_t			icon =	{				
		.rect					= { 0, 10, 48, 48 },
		.pad = { 20, 10, 10, 10}, 
		.background				= BODY_COLOR,
		//.attribute.blend		= true,
		.name="my.view.icon",
	};

	widget_params_t			icon_info = 		{		
		.rect	= { 50, 10, 46, 46 },		
		//.pad = { 20, 10, 10, 10}, 
		.background				= BODY_COLOR,
		//.attribute.blend		= true,
		.name="my.view.icon2",
	};

	widget_params_t			icon_yellow =
	{
		.rect					= { 50+50, 10, 46, 28 },
		//.pad = { 20, 10, 10, 10}, 
		.background				= BODY_COLOR,
		//.attribute.blend		= true,
		.name="my.view.icon3",
	};

	//
	
listbox_params_t		list =
	{
		WF_DOCK,
		W_PAD			= { 0, 4, 0, 0 },
		W_BACK			= (blit_source_t)0x80C0F0F0,
		.widget.name="my.view.list",
		.lines			= 12,
		.style			= &service_list_style,
	};
	scroll_params_t			scroll =
	{
		WR_DOCK,
		W_RECT			= { 0, 0, 20, 0 },
		W_PAD			= { 2, 2,  2, 2 },
		W_BACK			= 0x80588692,
		.widget.name="my.view.scroll",
		.thumb			= 0x80e8f7f7,
	};


	//

	
//button	
button_style_t			button_style =
	{ /* selected button */
		.pen[0].forecolor.value = 0x809e9e9e,/* 0x80848c8e, */
		//.pen[0].align 		= GfxALIGN_CENTER,
		.base[0]				= (blit_source_t)DATADIR"button.deselected.png",
		/* non-selected button */
						
		.pen[1].forecolor.value = 0x806A4700, /* 0x80ffffff : (blue)	0x806A4700: (yellow) */
		//.pen[1].align 		= GfxALIGN_CENTER,
		.base[1]				= (blit_source_t)DATADIR"button.selected.yellow.png"
	};
	button_params_t 		button =
	{
		.widget.rect	= { 280, 10, 168-20, 54 },
		.widget.pad 	= { 0, 0, 6, 0},
		.widget.name="my.view.button",
		//.widget.attribute.blend =1,
		.style			= &button_style,
	};



	//


	
/* order of widget_init */ 

	widget_init(&menu->widget, &base, (void*)NULL); 					
	WIDGET_VISIBLE(menu) = 0;   // it does not work !!
	//menu->widget.flags.visible = true;
	
	widget_border_init(&menu->border, out_border_list, 0, WIDGET_OF(menu));

	widget_init(&menu->top, &top, WIDGET_OF(menu)); 				menu->top.flags.visible	= 1;
	menu->top.custom.draw=label_custom_draw;
	widget_init(&menu->bottom, &help, WIDGET_OF(menu)); 			menu->bottom.flags.visible	= 1;
	widget_init(&menu->body, &body, WIDGET_OF(menu)); 			menu->body.flags.visible	= 1;



	widget_border_init(&menu->client, in_border_list, 0, &menu->body);

	icon.background = (blit_source_t)DATADIR"icon.critical.png";
	widget_init(&menu->icon, &icon, &menu->bottom); 	menu->icon.flags.visible = 1;

	icon_info.background = (blit_source_t)DATADIR"icon.info.png";
	widget_init(&menu->icon_info, &icon_info, &menu->bottom); 	menu->icon_info.flags.visible = 1;

	icon_yellow.background = (blit_source_t)DATADIR"icon.yellow.png";
	widget_init(&menu->icon_yellow, &icon_yellow, &menu->bottom); 	menu->icon_yellow.flags.visible = 1;

	//

	
//menu->listbox.scroll			= scroll_create(&menu->body, &scroll);
	//menu->listbox.list			= listbox_create(&menu->body, &list);
	//menu->listbox.list->scroll	= menu->listbox.scroll;
	//menu->listbox.list->item.draw	= draw_service_item;


	menu->scroll =scroll_create(&menu->body, &scroll);
	menu->list			= listbox_create(&menu->body, &list);
	menu->list->scroll	= menu->scroll;
	menu->list->item.draw	= draw_service_item;
	//..
	// button
	button.text 			= "ML(ML_OK)";
	menu->current=0;
	menu->button[0] 	= button_create(&menu->bottom, &button);
	
	button_set_state(menu->button[menu->current], BUTTON_SELECTED);
	//button_set_state(menu->button[menu->current], BUTTON_DISABLED); //something wrong

	//

// size for help 	
	menu->area.x	= menu->bottom.client.x+menu->bottom.rect.x;
	menu->area.y	= menu->bottom.client.y+ menu->bottom.rect.y;
	menu->area.w	= menu->bottom.client.w;
	menu->area.h	= menu->bottom.client.h;

	
	 d_print(" ------------->bottom size %d %d %d %d",menu->bottom.rect.x,menu->bottom.rect.y,menu->bottom.rect.w,menu->bottom.rect.h);

	return(0);
}


void make_sample_data(void)
{
	int i;
	ui_data_t 			*data;
	my_instance_t 		*menu = &menu_instance;
	ui_datalist_t *datalist= &menu->datalist;

	char *name[20]={"a1","a2","a3","a4","a5","a6","a7","a8","a9","a10","b1","b2","b3","b4","b5","b6","b7","b8","b9","b10"};
	

	ui_datalist_init(datalist);
	for(i=0;i<15;i++)
	{
	data = ui_data_new(name[i], (void *)(i+1));
	ui_datalist_add(datalist, data);
	}

	ui_datalist_add(datalist, ui_data_new("", null));

	#if 0
	ui_datalist_select(datalist, UI_DATA_FIRST);
	{
		ui_data_t 			*datum;
		dlink_foreach(datum, datalist->list)
		{
			print32(" %s - %d",datum->caption,(int)datum->object);
		}
	}
	#endif
	/* connect datalist to list object */
	listbox_set_datalist(menu->list, datalist);

	listbox_select(menu->list, UI_DATA_FIRST, false);


}
void my_widget_test()
{
	my_instance_t 		*menu = &menu_instance;
	my_view_layout(menu);
	// Need list for list box
	make_sample_data();
	widget_show(WIDGET_OF(menu), 1);
	{
		
		//unsigned int b_c;
		//gfx_rectangle_t granted = { 0,0,800,600};
		SDL_Surface *clip;
		SDL_Rect rect = {160,10,500,580};
		SDL_Rect bg = {0,0,800,600};
		Uint32 rmask, gmask, bmask, amask;
		int i,j=1;
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;

	
		clip=SDL_CreateRGBSurface(0,500,580,32,rmask,gmask,bmask,amask);
		if(clip == NULL) print("error \n");
		SDL_BlitSurface( screen, &rect, clip, NULL);

		
		//b_c=0x80000000;
		for(i=-500;i<300;i +=j)
		{
			j=j*2;
			print("----------------%d -- %d\n",j,i);
			//gfx_blit_fill(0,&granted,&b_c, NULL);
			SDL_FillRect(screen, &bg, 0x80000000);


			rect.x=i;
			rect.y=10;
			SDL_BlitSurface( clip, NULL, screen,&rect );
			SDL_Flip( screen );

		}
		
		SDL_FillRect(screen, &bg, 0x80000000);
		
		
		rect.x=300;
		rect.y=10;
		SDL_BlitSurface( clip, NULL, screen,&rect );
		SDL_Flip( screen );
		SDL_FreeSurface( clip );

	}


}






//-------------------------------------------------------
