
sdl03 :
	#gcc  -c sdl02.c  -I/usr/src/linux-headers-3.8.0-29/include/linux -I/usr/src/linux-headers-3.8.0-29/include/uapi/linux 
	gcc -Wall -g -c sdl03.c  
	gcc -g -c time.c
	gcc -g -c slink.c
	gcc -g -c th.c
	gcc -g  -c q.c
	gcc -Wall -g -c get_key.c
	gcc -g -c ui.control.c
	gcc -g -c live.control.c
	gcc -g -c live1.control.c
	gcc -g -c live2.control.c
	gcc -g -c live11.control.c
	gcc -g -c dlink.c
	gcc -g -c gt.c
	gcc -g -c widget.c
##	not yet tested
	gcc -g -c ui_data.c
	gcc -g -c listbox.c
	gcc -g -c scroll.c
##
	gcc -g -c button.c
	gcc -Wall -g -c my_view.c
##	
	gcc -Wall -g -c ui.view.c
	gcc -Wall -g -c my_view2.c

##
	gcc  -Wall -g -c zlist.c
	gcc -Wall -g -c xlist.c
	gcc -g -o sdl03 sdl03.o time.o xlist.o zlist.o slink.o th.o q.o  get_key.o ui.control.o live.control.o live1.control.o live2.control.o live11.control.o gt.o dlink.o widget.o ui_data.o listbox.o scroll.o button.o my_view.o ui.view.o my_view2.o `pkg-config  --cflags  --libs sdl` -lSDL_image  -lSDL_ttf

debug :
	# http://beej.us/guide/bggdb/
	# (gdb) run arg1 arg2
	# (gdb) display i
	# (gdb) info display
	# (gdb) undisplay 1
	# (gdb) watch i  [Hardware watchpoints are special breakpoints that will trigger whenever an expression changes]
	# (gdb) set (i = 20)
	## window function
	#(gdb) fs next
	#(gdb) fs src  //focus set to source window  //fs is Alias for focus
	#(gdb) fs cmd 
	#(gdb) layout [type] //src,asm,split.reg
	#(gdb) info win
	#(gdb) wh  CMD [val] //Alias winheight 
	#(gdb) wh  SRC [val] //Alias winheight 

	## core dump
	# ulimit -a
	# ulimit -c unlimited
	# gdb -tui -c core sdl03

	gdb -tui ./sdl3

clean :
	rm -f *.o
	rm -f sdl03

