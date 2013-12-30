/* The authors of this work have released all rights to it and placed it
in the public domain under the Creative Commons CC0 1.0 waiver
(http://creativecommons.org/publicdomain/zero/1.0/).

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Hello_World_(C,_Xlib)?oldid=19143

*/
/*
http://en.literateprograms.org/Hello_World_(C,_Xlib)

How to write "Hello world" in an X window using Xlib.
Most applications use higher level libraries to interact with the X server.

*/

#include<X11/Xlib.h>

#include<stdio.h>
#include<stdlib.h>

int main()
{
	Display *dpy;
	Window rootwin;
	Window win;
	Colormap cmap;
	XEvent e;
	int scr;
	GC gc;


	if(!(dpy=XOpenDisplay(NULL)))   // need a connection to the X server
	{
		fprintf(stderr, "ERROR: could not open display\n");
		exit(1);
	}
	scr = DefaultScreen(dpy);
	rootwin = RootWindow(dpy, scr);
	cmap = DefaultColormap(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, 100, 50,
			0,  //border_width 
			BlackPixel(dpy, scr), //border_color 
			BlackPixel(dpy, scr)  //background color
		);
	XStoreName(dpy, win, "hello");

	gc=XCreateGC(dpy, win, 0, NULL);
	XSetForeground(dpy, gc, WhitePixel(dpy, scr));
	
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask); // To select which events to receive 
	
	XMapWindow(dpy, win);  // To make the X server show it
	
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1)
			XDrawString(dpy, win, gc, 10, 10, "Hello World!", 12);
		else if(e.type==ButtonPress) break;
	}

	XCloseDisplay(dpy);

	return 0;
}
