#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

GdkPixbuf *create_pixbuf(const gchar * filename)
{
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   if(!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

gint count = 0;
char buf[5];

void increase(GtkWidget *widget, gpointer label)
{
  count++;

  sprintf(buf, "%d", count);
  gtk_label_set_text(label, buf);
	g_print("clicked +\n");
}

void decrease(GtkWidget *widget, gpointer label)
{
  count--;

  sprintf(buf, "%d", count);
  gtk_label_set_text(label, buf);
	
	g_print("clicked -\n");
}

void frame_callback(GtkWindow *window, 
      GdkEvent *event, gpointer data)
{
   int x, y;
   char buf[10];
   x = event->configure.x;
   y = event->configure.y;
   sprintf(buf, "%d, %d", x, y);
   gtk_window_set_title(window, buf);
}
void enter_button(GtkWidget *widget, gpointer data) 
{ 
  GdkColor color;
  color.red = 27000;
  color.green = 30325;
  color.blue = 34181;
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &color);
}

int main( int argc, char **argv)
{
  GtkWidget *label;
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *plus;
  GtkWidget *minus;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 250, 180);
  gtk_window_set_title(GTK_WINDOW(window), "+-");
	gtk_widget_add_events(GTK_WIDGET(window), GDK_CONFIGURE);


  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

  plus = gtk_button_new_with_label("+");
  gtk_widget_set_size_request(plus, 80, 35);
  gtk_fixed_put(GTK_FIXED(frame), plus, 50, 20);

  minus = gtk_button_new_with_label("-");
  gtk_widget_set_size_request(minus, 80, 35);
  gtk_fixed_put(GTK_FIXED(frame), minus, 50, 80);

  label = gtk_label_new("0");
  gtk_fixed_put(GTK_FIXED(frame), label, 190, 58); 

  gtk_widget_show_all(window);

  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);

  g_signal_connect(plus, "clicked", 
      G_CALLBACK(increase), label);

  g_signal_connect(minus, "clicked", 
      G_CALLBACK(decrease), label);

	g_signal_connect(plus, "clicked", 
				G_CALLBACK(enter_button), NULL);

	g_signal_connect(G_OBJECT(window), "configure-event",	G_CALLBACK(frame_callback), NULL);

	g_signal_connect_swapped(G_OBJECT(window), "destroy",  G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return 0;

}

#if 0
int main( int argc, char *argv[])
{
	GtkWidget *window;


	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	{
		gtk_window_set_title(GTK_WINDOW(window), "icon");
		//gtk_window_set_title(GTK_WINDOW(window), "Center");
		gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		
		//gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("/home/my2/1.png"));
	}	

	gtk_widget_show(window);
	{
		//to quit, connect destory signal  to the gtk_main_quit 	
		g_signal_connect_swapped(G_OBJECT(window), "destroy",  G_CALLBACK(gtk_main_quit), NULL);
	}	
	gtk_main();  //just waiting event from X server

	return 0;
}
#endif

