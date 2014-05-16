#
# http://www.gnu.org/software/make/manual/make.html
#


CC:=gcc
INCLUDES:=$(shell pkg-config --cflags libavformat libavcodec libswscale libavutil sdl)
CFLAGS:=-Wall -ggdb -g
LDFLAGS:=$(shell pkg-config --libs libavformat libavcodec libswscale libavutil sdl) 
EXE:=tutorial01.out tutorial02.out tutorial03.out tutorial04.out\
	tutorial05.out tutorial06.out tutorial07.out

#
# This is here to prevent Make from deleting secondary files.
#
.SECONDARY:
	

#
# $< is the first dependency in the dependency list
# $@ is the target name
#
info:
	@echo HOME=$(HOME)
	@echo PKG_CONFIG_PATH=$(PKG_CONFIG_PATH)
		
all: dirs $(addprefix bin/, $(EXE)) tags
#all: dirs $(addprefix bin/, $(EXE)) 

dirs:
	mkdir -p obj
	mkdir -p bin

tags: *.c
	ctags *.c

bin/%.out: obj/%.o
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

obj/%.o : %.c
	$(CC) $(CFLAGS) $< $(INCLUDES) -c -o $@


run:
	@echo run	
	./bin/tutorial02.out 2.avi
	
debug:	
	@echo debug
	gdb  ./bin/tutorial02.out 
	
debug2:	
	@echo debug
	gdb -tui ./bin/tutorial02.out 

clean:
	rm -f obj/*
	rm -f bin/*.out
	rm -f tags
	rm -f bin/*.ppm
