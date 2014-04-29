TARGET=test01
CFLAGS=-Wall -g -I.
LFLAGS=
info :

	@echo " make all"
	@echo " make debug"
	@echo " make clean"

all : $(TARGET)

main.o : main.c task.h sys.h
	gcc -c $< -o $@ $(CFLAGS)
task.o : task.c task.h sys.h
	gcc -c $< -o $@ $(CFLAGS)
sys.o: sys.c sys.h
	gcc -c $< -o $@ $(CFLAGS)

counter_task.o : counter_task.c counter_task.h
	gcc -c $< -o $@ $(CFLAGS)
get_key.o : get_key.c get_key.h
	gcc -c $< -o $@ $(CFLAGS)
q.o : q.c q.h
	gcc -c $< -o $@ $(CFLAGS)

$(TARGET): main.o task.o sys.o counter_task.o get_key.o q.o
	gcc -o $@ $^ -pthread -lpthread








$(TARGET)-old :
	gcc -Wall -g -c  main.c  
	gcc -Wall -g -c task.c
	gcc -g -pthread -lpthread -o $(TARGET) main.o  task.o

debug :
	# http://beej.us/guide/bggdb/
	# (gdb) b main
	# (gdb) r or run arg1 arg2
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

	gdb -tui ./$(TARGET)

clean :
	rm -f *.o
	rm -f $(TARGET)

