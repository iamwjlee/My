#
# http://www.gnu.org/software/make/manual/make.html
#
#
#  audio break pb
#  if (codecCtx->sample_fmt == AV_SAMPLE_FMT_S16P) {
#  codecCtx->request_sample_fmt = AV_SAMPLE_FMT_S16;
# }
#  codec = avcodec_find_decoder(codecCtx->codec_id);
#  if(!codec || (avcodec_open2(codecCtx, codec, &optionsDict) < 0)) {
#    fprintf(stderr, "Unsupported codec!\n");
#   return -1;
#  }


CC:=gcc
INCLUDES:=$(shell pkg-config --cflags libavformat libavcodec libswscale libavutil sdl)
CFLAGS:=-Wall -ggdb -g
LDFLAGS:=$(shell pkg-config --libs libavformat libavcodec libswscale libavutil sdl) 
EXE:=tutorial01.out tutorial02.out tutorial03.out tutorial04.out\
	tutorial05.out tutorial06.out tutorial07.out audio_tone.out

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




run0:
	@echo run0	
	./bin/tutorial03.out 1.avi
run3:
	@echo run3	
	./bin/tutorial03.out 1.avi

run4:
	@echo run4	
	./bin/tutorial04.out 1.avi
run7:
	@echo run7	
	./bin/tutorial07.out 1.avi

run:
	@echo run	
	./bin/tutorial03.out 2.avi

run2:
	@echo run2	
	./bin/tutorial02.out http://192.168.0.37:8080/genitek/2.avi
debug0:
	@echo debug0	
	gdb --args ./bin/tutorial02.out http://192.168.0.37:8080/genitek/2.avi


debug:	
	@echo debug
	gdb  ./bin/tutorial02.out 
	
debug2:	
	@echo debug
	gdb -tui ./bin/tutorial02.out 
debug3:
	@echo debug3
	gdb -tui --args ./bin/tutorial02.out   http://192.168.0.37:8080/genitek/2.avi
debug4:
	gdb -tui --directory . -x gdb.cmd

clean:
	rm -f obj/*
	rm -f bin/*.out
	rm -f tags
	rm -f bin/*.ppm
