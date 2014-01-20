#include "my_sdl.h"
#include "q.h"
#include "ui.control.h"


#include "widget.h"
#include"dlink.h"
#include "slink.h"

#include "menuitem.h"
//#include <directfb.h>
//#include "label.h"

 
#define d_print(...)  printf(__VA_ARGS__)
 
#define T_DOCK							.align = GfxDOCK_TOP
#define B_DOCK							.align = GfxDOCK_BOTTOM
#define L_DOCK							.align = GfxDOCK_LEFT
#define R_DOCK							.align = GfxDOCK_RIGHT
#define F_DOCK							.align = GfxDOCK_FILL

#define PNG(n)							(const char*)(n)
 void widget_align(gfx_rectangle_t *clientRect, widget_t *child, gfx_align_t align);
 void widget_dock(gfx_rectangle_t *clientRect, widget_t *child, gfx_align_t align);

void widget_show(widget_t *widget, int force_update);

extern  SDL_Surface *load_image( const char *name );


// -----------------------------------------------------




 typedef struct
 {
	slink_t 				slink;										
	menu_t					*parent;									
	const char				*name;										
	widget_t				widget; 								
	widget_border_t 		border; 								
	widget_t				body; 								
	U32 					level;									
	U32 					dummy;
   	widget_border_t		 client;
	 widget_t 			 bottom;
	 widget_t 			 *title;

	
 //  task_t 				 *task;
 	gfx_rectangle_t			area;
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

 int my_view_layout(my_instance_t *menu)
{
 // widget_params_t 		base	= { .rect = { 30, 30, 200, 600 }, 	 .background =	NULL, .name="base"};
	
	widget_params_t base	= { .rect = { 60, 60, 500, 400 },  .attribute.popup = 1, .background =	0x808f0000, .name="my.view.base"};
  	widget_params_t help  = { .rect = { 0, 0, 0, 150},  .pad = { 0, 0, 10, 0},  .align = GfxDOCK_BOTTOM,.background = 0x800070A0,.name="my.view.help" };
	widget_params_t body	= { .rect = { 0, 0,  0, 0 },			.align = GfxDOCK_FILL,	.background = 0x80c0f0f0,.name="my.view.body" };
	
	

	/* order of widget_init */ 

	/* fill base region with red color */
	widget_init(&menu->widget, &base, (void*)NULL); 					WIDGET_VISIBLE(menu) = 0;   
	//menu->widget.flags.visible = true;
	widget_border_init(&menu->border, out_border_list, 1, WIDGET_OF(menu));

	
	widget_init(&menu->bottom, &help, WIDGET_OF(menu)); 						menu->bottom.flags.visible	= 1;
	widget_init(&menu->body, &body, WIDGET_OF(menu)); 					menu->body.flags.visible	= 1;



	widget_border_init(&menu->client, in_border_list, 1, &menu->body);




// size for help 
	menu->area.x	= menu->bottom.client.x+menu->bottom.rect.x;
	menu->area.y	= menu->bottom.client.y+ menu->bottom.rect.y;
	menu->area.w	= menu->bottom.client.w;
	menu->area.h	= menu->bottom.client.h;

	
	 d_print(" ------------->bottom size %d %d %d %d\n",menu->bottom.rect.x,menu->bottom.rect.y,menu->bottom.rect.w,menu->bottom.rect.h);

	return(0);
}


void  my_widget_test()
{
	my_instance_t 		*menu = &menu_instance;
	my_view_layout(menu);

	widget_show(WIDGET_OF(menu), 1);

}






//-------------------------------------------------------

 int widget_border_clear(widget_border_t *border)
 {
	 memset(border, 0, sizeof(widget_border_t));
	 return(0);
 }

 int widget_border_init(widget_border_t *border, blit_source_t *backgrounds, BOOL blend, widget_t *widget)
 {
	unsigned int			 *background;
	 blit_source_t			 *blit_source;
	 widget_plate_t 		 *plate;
	 int					 i;
	 int w,h;

	unsigned int tmp;
	
	 
	 SDL_Surface *background_image;
	 
	 widget_params_t		 base = { .rect = { 0, 0, 24, 24 }, T_DOCK,  .attribute.phantom = TRUE	};

	 for(i = 0,  blit_source = backgrounds; i < 2; i++)
	 {
			tmp = *blit_source++;
				d_print("%s [0x%x]\n",(const char *)tmp,tmp);
			tmp = *blit_source++;
			d_print("%s \n",(const char *)tmp);

			tmp = *blit_source++;
			
			d_print("%s \n",(const char *)tmp);
	 }	 
 
	 for(i = 0, plate = &border->_top, blit_source = backgrounds; i < 2; i++, plate++)
	 {
		 widget_params_t		 base_l  = { .rect = { 0, 0, 24, 0 }, L_DOCK, .background = *blit_source++, .attribute.blend = blend, .name="base_l" };
		 widget_params_t		 base_r  = { .rect = { 0, 0, 24, 0 }, R_DOCK, .background = *blit_source++, .attribute.blend = blend, .name="base_r" };
		 widget_params_t		 base_m  = { .rect = { 0, 0,  0, 0 }, F_DOCK, .background = *blit_source++, .attribute.blend = blend , .name="base_m"};
 
		// if(((base_l.background >> 24) > 0x80) && 1 /* (base_l.background != BLIT_SOURCE_NONE) */)
		 {
			 background_image = load_image(PNG(base_l.background));
			 if(background_image)
			 {
			 	
				//background_image->GetSize( background_image, &w, &h );
				base_l.rect.w =background_image->w;
				base.rect.h = background_image->h;
			 }
		 }
		 //if(((base_r.background >> 24) > 0x80) &&1 /* (base_r.background != BLIT_SOURCE_NONE) */)
		 {
			 background_image = load_image(PNG(base_r.background));
			 if(background_image)
			 	{
					
					base_r.rect.w =background_image->w;
				 
			 	}
		 }
 
		 widget_init(WIDGET_OF(plate),		 &base, 	 widget);		 WIDGET_VISIBLE(plate)		 = TRUE;
		 widget_init(WIDGET_OF(&plate->l),	 &base_l,	 WIDGET_OF(plate)); 	 WIDGET_VISIBLE(&plate->l)	 = TRUE;
		 
		 d_print("         %s \n",(const char *)base_l.background);
		 widget_init(WIDGET_OF(&plate->r),	 &base_r,	 WIDGET_OF(plate)); 	 WIDGET_VISIBLE(&plate->r)	 = TRUE;
		 widget_init(WIDGET_OF(&plate->m), &base_m, WIDGET_OF(plate));  WIDGET_VISIBLE(&plate->m)	 = TRUE;
		 base.align = GfxDOCK_BOTTOM;
	 }
 
	 {
		 widget_params_t		 base_l  = { .rect = { 0, 0, 24, 0 }, L_DOCK, .background = *blit_source++,.name="base_w", .attribute.blend = blend};
		 widget_params_t		 base_r  = { .rect = { 0, 0, 24, 0 }, R_DOCK, .background = *blit_source++, .name="base_e", .attribute.blend = blend};
 
		 //if(((base_l.background >> 24) > 0x80) && 1 /*(base_l.background != BLIT_SOURCE_NONE)*/)
		 {
			 background_image =load_image(PNG(base_l.background));
			 if(background_image) 	{ 
			 	
			 	base_l.rect.w = background_image->w;
				
			 	
			}
		 }
		 //if(((base_r.background >> 24) > 0x80) &&1 /* (base_r.background != BLIT_SOURCE_NONE)*/)
		 {
			 background_image = load_image(PNG(base_r.background));
			 if(background_image) {
			 	
			 	base_r.rect.w =background_image-> w;
			 	
			 }	
		 }
		 widget_init(WIDGET_OF(&border->l),  &base_l,	 widget);		 WIDGET_VISIBLE(&border->l)  = TRUE;
		 widget_init(WIDGET_OF(&border->r),  &base_r,	 widget);		 WIDGET_VISIBLE(&border->r)  = TRUE;
	 }
 
	 if(WIDGET_OF(&border->_top.l)->rect.w < WIDGET_OF(&border->_bot)->rect.h)
		 widget->client.h += WIDGET_OF(&border->_bot)->rect.h - WIDGET_OF(&border->_top.l)->rect.w;


	 return(0);
 
 }

#if 0
static void label_custom_draw2(widget_t *widget, int *target, gfx_rectangle_t *granted, int recursive)
{
	char text[30];
	label_t *label=(label_t *)widget;
	
	/* This is the same meaning !:  gfx_rectangle_t		client	= label->widget.client; */
	gfx_rectangle_t 		client	= widget->client;

 d_print("label_custom_draw2 : client[%d-%d-%d-%d] granted[%d-%d-%d-%d]0x%x\n ",
 client.x, client.y,client.w,client.h,	granted->x,granted->y,granted->w,granted->h,widget->background);

	client.x += granted->x;
	client.y += granted->y;
	
 
 	//gfx_pen_set_target(pen, target, &client);
	//label->remain = gfx_new_puts(pen, label->text);
	
 	gfx_blit_label(0,label->label_text,&client,label->label_color);
	
}
#endif


int widget_init(widget_t *widget, widget_params_t *params, widget_t *parent)
{
	//DEBUG_ASSERT(widget && params);

	//parent=DISPLAY_HD; ///??? bause of duplicated
	//if((U32)parent!=0) d_print("parent is not Zero in the widget_init \n");
	//if(((U32)parent == _DISPLAY_HD) || ((U32)parent == _DISPLAY_SD)) // ????
	if(parent==NULL)
	{
		widget->parent	= NULL;
		//widget->target	= &GFX_GXOBJ_Bitmap[2]; //   &gfx.viewport[_DISPLAY_HD].surface.buffer[1].bitmap;
	}
	else
	{
		widget->parent	= parent;
		if(parent)
			widget->target	= parent->target;
	}

	if(params->target)
		widget->target = params->target;

	//DEBUG_ASSERT(widget->target);
	strcpy(widget->name,params->name);
	widget->attribute	= params->attribute;
	widget->rect		= params->rect;
	widget->background	= params->background;  // error: assignment of read-only member ‘background’
	
	//widget->cover		= params->cover ? params->cover : BLIT_SOURCE_NONE;  

	#if 0
	widget->label_color=params->label_color;
	if(params->label_text)
	strcpy(widget->label_text,params->label_text);
	#endif
	
	widget->flags.dirty = 1;
	widget->flags.visible = 0;

	if(widget->parent)
	{
		if(params->align & GfxALIGN_SAME_AS_LAST)
		{
			widget_t				*last = dlink_last_of(parent->children.list);

			widget->rect	= last->rect;
			widget->client	= last->client;
		}
		else
		{
			if(params->align & GfxALIGNMENT_DOCK)		widget_dock(&parent->client, widget, params->align);
			else if(params->align & GfxALIGNMENT_ALIGN)	widget_align(&parent->client, widget, params->align);

			if(widget->target == parent->target)
			{
				widget->rect.x += parent->rect.x;
				widget->rect.y += parent->rect.y;
			}
		}
		dlink_append(parent->children.list, widget);
		parent->children.count++;
	}
	else	/* target must be viewport surface */
	{
		gfx_rectangle_t			client; // = RECTANGLE_ZERO;

		client.w = 800; //widget->target->Width;
		client.h =  600; //widget->target->Height;
		if(params->align & GfxALIGNMENT_DOCK)	{
			widget_dock(&client, widget, params->align);
		}	
		else if(params->align & GfxALIGNMENT_ALIGN)	{
			widget_align(&client, widget, params->align);
		}	
	}

	widget->client.x = params->pad.l;
	widget->client.y = params->pad.t;
	widget->client.w = widget->rect.w - (params->pad.l + params->pad.r);
	widget->client.h = widget->rect.h - (params->pad.t + params->pad.b);

	return(0);
}
void widget_align(gfx_rectangle_t *clientRect, widget_t *child, gfx_align_t align)
{
	gfx_rectangle_t			*rect = &child->rect;

	if((clientRect->w > 0) && (clientRect->h > 0))
	{
		if(rect->h > clientRect->h)		rect->h = clientRect->h;
		if(rect->w > clientRect->w)		rect->w = clientRect->w;
		if(rect->x < 0)					rect->x = 0;
		if(rect->y < 0)					rect->y = 0;

		if(align & GfxALIGNMENT_TOP)
			rect->y += clientRect->y;
		else if(align & GfxALIGNMENT_MIDDLE)
			rect->y = clientRect->y + ((clientRect->h - rect->h) / 2);
		else if(align & GfxALIGNMENT_BOTTOM)
			rect->y = clientRect->y + clientRect->h - rect->h - rect->y;
		else if(align & GfxALIGNMENT_TRAIL_V)
		{
			widget_t			*prev = dlink_prev_of(child);
			widget_t			*parent = child->parent;	//DEBUG_ASSERT(parent != null);

			if(prev != child)
			{	/* prev->rect은 이미 parent의 offset까지 더해져있고,
				gfx_widget_alig()은 parent의 clientRect에서부터의 offset이므로
				parent의 offset은 빼줌 */
				if(child->target == parent->target)
				{
					rect->y = prev->rect.y + prev->rect.h - parent->rect.y;
					rect->x = prev->rect.x - parent->rect.x;
				}
				else
				{
					rect->y = prev->rect.y + prev->rect.h;
					rect->x = prev->rect.x;
				}

			}
		}

		if(align & GfxALIGNMENT_LEFT)
			rect->x += clientRect->x;
		else if(align & GfxALIGNMENT_CENTER)
			rect->x = clientRect->x + ((clientRect->w - rect->w) / 2);
		else if(align & GfxALIGNMENT_RIGHT)
			rect->x = clientRect->x + clientRect->w - rect->w - rect->x;
		else if(align & GfxALIGNMENT_TRAIL_H)
		{
			widget_t			*prev = dlink_prev_of(child);
			widget_t			*parent = child->parent;	//DEBUG_ASSERT(parent != NULL);

			if(prev != child)
			{
				if(child->target == parent->target)
				{
					rect->x = prev->rect.x + prev->rect.w - parent->rect.x;
					rect->y = prev->rect.y - parent->rect.y;
				}
				else
				{
					rect->x = prev->rect.x + prev->rect.w;
					rect->y = prev->rect.y;
				}
			}
		}

		if(rect->y + rect->h > clientRect->y + clientRect->h)
			rect->h = clientRect->y + clientRect->h - rect->y;
		if(rect->x + rect->w > clientRect->x + clientRect->w)
			rect->w = clientRect->x + clientRect->w - rect->x;
	}
	else
	{
		rect->x = rect->y = 0;
		rect->w = rect->h = 0;
	}
}

void widget_dock(gfx_rectangle_t *clientRect, widget_t *child, gfx_align_t align)
{
	gfx_rectangle_t			*rect = &child->rect;

	//DEBUG_ASSERT(clientRect->w && clientRect->h);
	if((clientRect->w > 0) && (clientRect->h > 0))
	{
		gfx_rectangle_t			client, *remain = clientRect;

		if(align & GfxDOCK_PHANTOM)
		{
			client = *clientRect;
			remain = &client;
		}

		switch(align & 0x0FFFFFFF)
		{
			case GfxDOCK_TOP : 		rect->x = remain->x;
									rect->y = remain->y;
									rect->w = remain->w;
									if(rect->h > remain->h)
										rect->h = remain->h;

									remain->y += rect->h;
									remain->h -= rect->h;
									break;

			case GfxDOCK_BOTTOM : 	if(rect->h > remain->h)
										rect->h = remain->h;
									rect->x = remain->x;
									rect->y = remain->y + remain->h - rect->h;
									rect->w = remain->w;

									remain->h -= rect->h;
									break;

			case GfxDOCK_LEFT : 	rect->x = remain->x;
									rect->y = remain->y;
									rect->h = remain->h;
									if(rect->w > remain->w)
										rect->w = remain->w;

									remain->x += rect->w;
									remain->w -= rect->w;
									break;

			case GfxDOCK_RIGHT : 	if(rect->w > remain->w)
										rect->w = remain->w;
									rect->x = remain->x + remain->w - rect->w;
									rect->y = remain->y;
									rect->h = remain->h;

									remain->w -= rect->w;
									break;

			case GfxDOCK_FILL :		memcpy(rect, remain, sizeof(gfx_rectangle_t));
									remain->x = 0;	remain->y = 0;
									remain->w = 0;	remain->h = 0;
									break;

			default:				break;
		}
	}
	else
	{
		rect->x = rect->y = 0;
		rect->w = rect->h = 0;
	}
}
BOOL widget_clear(widget_t *widget)
{
	if(widget)
		memset(widget, 0, sizeof(widget_t));
	return(false);
}

BOOL widget_dock_space(widget_t *parent, widget_params_t *params)
{
	//DEBUG_ASSERT(parent && params && (params->align & GfxALIGNMENT_DOCK));

	if(parent->client.w && parent->client.h)
	{
		switch(params->align & 0x0FFFFFFF)
		{
			case GfxDOCK_TOP: 		parent->client.y += params->rect.h;
			case GfxDOCK_BOTTOM:	parent->client.h -= params->rect.h;
									break;

			case GfxDOCK_LEFT: 		parent->client.x += params->rect.w;
			case GfxDOCK_RIGHT:		parent->client.w -= params->rect.w;
									break;
			default:				break;
		}
	}
	return(false);
}

int widget_is_visible(widget_t *widget)
{
	if(widget)
	{
		while(widget)
		{
			if(!widget->flags.visible)
				return(0);
			widget = widget->parent;
		}
		return(1);
	}
	return(0);
}

void widget_show_recursive(widget_t *widget, int force_update)
{
	if(widget && widget->flags.visible)
	{
		widget_t				*child;

		if((force_update || widget->flags.dirty) && !widget->attribute.phantom)
		{
			gfx_rectangle_t			granted = widget->rect;  //real size
			gfx_rectangle_t 		client	= widget->client;

			if(widget->attribute.blend)
			{
				//gfx_blit_fill(BLIT_MODE_BLEND, widget->target, &granted, &widget->background, null);
				//d_print(" gfx_blit_fill blend\n");
				d_print("\n");
				d_print(" gfx_blit_fill blend [%d-%d-%d-%d][%d-%d-%d-%d][0x%x]-%s\n",client.x,client.y,client.w,client.h,granted.x, granted.y,granted.w,granted.h,widget->background,widget->name);
				//gfx_blit_image(&granted ,&widget->background, NULL);
				
				gfx_blit_fill(1,&granted,&widget->background, NULL);
			}	
			else
			{
				//gfx_blit_fill(BLIT_MODE_COPY, widget->target, &granted, &widget->background, null); //here
				
				d_print(" gfx_blit_fill not blend [%d-%d-%d-%d][%d-%d-%d-%d][0x%x] -%s\n",client.x,client.y,client.w,client.h,granted.x, granted.y,granted.w,granted.h,widget->background,widget->name);
				//gfx_blit_fill_color(&granted,&widget->background);
				if(granted.w && granted.h)
				gfx_blit_fill(0,&granted, &widget->background, NULL);
			}	
			/* some case we don't need to upgrade custom.draw back ground before custom.draw,label display*/

			if(widget->custom.draw)
				widget->custom.draw(widget, widget->target, &granted, 0);

			//gfx_blit_fill(BLIT_MODE_BLEND, widget->target, &granted, &widget->cover, null); //here again but nothing  widget->cover??
			force_update = 1;
		}

		dlink_foreach(child, widget->children.list)
		{
			print(" recursive [%s] \n",child->name);
			widget_show_recursive(child, force_update);
		}	
		widget->flags.dirty = 0;
	}
}


void widget_show(widget_t *widget, int force_update)
{
	if(widget)
	{
		print47("\twidget_show start ---->%s",widget->name);
		if(!widget->flags.visible)
		{
			force_update = 1;
			widget->flags.visible = 1;
		}

		if(widget_is_visible(widget))
		{
			if(force_update || widget->flags.dirty)
			{
#if 0
				//if(widget->target ==  HD_VIEWPORT_BACK_BITMAP)
				{
					if(	!widget->capture && widget->attribute.popup)
					{
						print("widget capture first -\n");
						widget->capture= gfx_surface_claim(&widget->rect);
						if(widget->capture)
						{
							
							gfx_blit_capture(&widget->rect,widget->capture,NULL);


						}
						//widget->capture = gfx_blitbuf_claim(GFX_GXOBJ_Bitmap[0].ColorType, &widget->rect);
						//if(widget->capture)
						{
							//gfx_blit_image(BLIT_MODE_COPY| BLIT_DELETE_SOURCE, widget->capture, null, HD_VIEWPORT_BACK_BITMAP, &widget->rect);
						}
					}
				}
#endif
				widget_show_recursive(widget, force_update); //here
			}
			else
			{
				widget_t				*child;

				dlink_foreach(child, widget->children.list)
					widget_show_recursive(child, force_update);
			}

		}
		else if(force_update)
			widget->flags.dirty = 1;

		
		print47("\twidget_show stop <----%s",widget->name);
		print("\n");
	}
}



void widget_hide(widget_t *widget)
{
	if(widget)
	{
		gfx_rectangle_t			*rect	= &widget->rect;

		widget->flags.visible = false;
		if(widget->capture)
		{
			d_print(" widget_hide : capture restore\n");
			gfx_blit_restore(rect,widget->capture);
			//gfx_blit_image(BLIT_MODE_COPY| BLIT_DELETE_SOURCE, HD_VIEWPORT_BACK_BITMAP, rect, widget->capture, null);
			widget->capture = null;
		}
		else if(widget->attribute.popup || !widget->parent)
		{
			//if(widget->target)
			if(1)
			{
				gfx_color_t c;
				d_print(" widget_hide : ------%d %d %d %d\n",rect->x,rect->y,rect->w,rect->h);
				c.value=0x80ffffff;
				gfx_blit_fill_color(0, rect,  &c);
	//			clear_surface();
			}	
			else
				d_print(" widget_hide fail\n");
		}
		else
			
		d_print(" widget_hide fail2\n");
	}
}

// ---------------------------gfx.c---------------------




