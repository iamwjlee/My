CC = gcc

ubuntu:
	# version 12.04 

	# -------gvim install ----------
	# sudo apt-get install vim-gnome
	# add in ~/.bashrc the line
	# function gvim () { /usr/bin/gvim -f $* & }

	# ------- Samba install ----------
	# apt-get install samba smbfs
	# sudo smbpasswd -a wj
	# sudo vi /etc/samba/smb.conf
	# 	[wj]
	# 	comment = samba directory
	# 	path = /home
	# 	valid users = wj
	# 	public = yes
	# 	writable = yes
	#
	# sudo service smbd restart
	# 
	# \\192.168.0.42\wj   at the win7


help:
	@echo -- usefull command --
	
	#sudo apt-cache search libpng
	#sudo apt-cache search libjpeg
	#sudo apt-cache search libfreetype
	#sudo apt-get install libjpeg62-dev



a: 
	@echo --hello with xlib --
	#@echo --pkg-config --list-all | grep X11
	#sudo apt-get install libx11-dev ................. for X11/Xlib.h
	$(CC)  -c hello-xlib.c  -o hello-xlib.o  -Wall -I/usr/include/X11
	$(CC) -o hello-xlib  hello-xlib.o  -L/usr/lib/i386-linux-gnu    -lX11 

b : 
	#@echo --pkg-config --list-all | grep cairo
	@echo --hello with cairo --
	#sudo apt-get install libcairo2-dev
	$(CC)  -c hello-cairo.c  -o hello-cairo.o  -Wall -pedantic -g  `pkg-config --cflags cairo`
	$(CC) -o hello-cairo  hello-cairo.o  -Wall -g `pkg-config --libs cairo`  -lX11        

c : 
	@echo --check glib  -----------------
	#@echo --pkg-config --list-all | grep glib
	#@echo --dpkg -l | grep libglib*
	#@echo ----------------------------
	gcc  -c glist.c  -o glist.o  -Wall   `pkg-config --cflags glib-2.0`
	#gcc  -c glist.c  -o glist.o  -Wall   -I/usr/local/include/glib-2.0 -I/usr/local/lib/glib-2.0/include 
	gcc -o glist  glist.o  -Wall  `pkg-config --libs glib-2.0`        

d: 
	@echo --check zlib  -----------------
	#@echo --pkg-config --list-all | grep zlib
	#@echo --pkg-config --libs zlib


gtk0:
	#echo --need gtk+ ------------
	#sudo apt-get install libgtk2.0-dev
	gcc -c gtk0.c `pkg-config  --cflags gtk+-2.0`
	gcc -o gtk0 gtk0.o `pkg-config --libs gtk+-2.0`

gtk1:
	#echo --need gtk+ ------------
	#sudo apt-get install libgtk2.0-dev
	gcc -c gtk1.c `pkg-config  --cflags gtk+-2.0`
	gcc -o gtk1 gtk1.o `pkg-config --libs gtk+-2.0`

directfb:
	@echo -- change booting option and add module vesafb and make initramfs image again
	# //$ sudo vi /etc/default/grub
        #  //add 'vga=789' 
   	#  //$ sudo update-grub
	# $ sudo vi /etc/initramfs-tools/module
        # add 'fbcon' and 'vesafb'
        # $ sudo vi /etc/modprobe.d/blacklist-framebuffer
        # disable 'blacklist vesafb'
        # $ sudo update-initramfs -u
	# $ sudo reboot

         
	# vga=789(800x600,24bit)
	# vga=791(1024x768,16bit)
	# vga=792(1024x768,24bit)
        # To change kernel option ,
	# sudo vi /boot/grub/menu.list
	# sudo vi /etc/default/grub
	#   add  vga=791  by sudo vi /etc/default/grub and then sudo upgate-grub
	# sudo reboot
	# dmesg | grep framebuffer
	# dmesg | grep vesafb
	# tar xvfz DirectFB-1.6.2.tar.gz 
	# after .configure make install, ldconfig for cache
	#sudo dfbinfo
	#~/.directfbrc
	#system=fbdev
	#fbdev=/dev/fb0
	#mode=1024x768
	#or 
	#mode=1024x768
	#
	# add path in the  vi /etc/ld.so.conf
	# caching by ldconfig 



dfb02:   
	@echo --check directfb  -----------------
	#@echo --fusion : Fusion IPC High Level IPC Mechanisms  -----------------
	#@echo  tar xvfz DirectFB-1.6.2.tar.gz  -----------------
	#./configure
	#sudo apt-cache search libjpeg
	#sudo apt-get install libjpeg62-dev
	#gcc -c dfb02.c -I /usr/local/include/directfb
	#gcc -o dfb02 dfb02.o   -L/usr/local/lib -ldirectfb 
	#./dfb02: error while loading shared libraries: libdirectfb-1.6.so.0: cannot open shared object file: No such file or directory
	# solved by ldconfig
	
	gcc -c dfb02.c `pkg-config --cflags directfb`
	gcc -o dfb02 dfb02.o   `pkg-config --libs directfb`

dfb01:   

	gcc -c dfb01.c  -I /usr/local/DirectFB/include/directfb
	gcc -o dfb01 dfb01.o   -L/usr/local/DirectFB/lib -ldirectfb 


gl:
	@echo --OpenGL is not include window output ----------
	#pkg-config --list-all | grep gl
	# gl: basic rendering function 
	# glu : advance function
	# glut(gl utility toolkit) : support window  and keyboard/mouse event.
	# sudo apt-get install freeglut3-dev
	g++ -c gl.cpp 
	g++ -o gl gl.o -lglut -lGLU


sdl:
	@echo --sdl example ----------
	## setting up SDL Extension for g++ , add -lSDL_image or -lSDL_ttf or -lSDL_mixer
	# sudo apt-get install libsdl1.2-dev
	# sudo apt-get install libsdl-image1.2-dev
	# I(large i) Include    l(small L) library
	# libsdl-ttf2.0-dev
	# libsdl-mixer1.2-dev
	#gcc  -c sdl.c 
	#gcc  -o sdl sdl.o -I/usr/include/SDL -lSDL -lSDL_image  

	gcc  -c sdl.c 
	gcc -o sdl sdl.o `pkg-config  --cflags  --libs sdl` -lSDL_image

sdl01:
	gcc  -c sdl01.c 
	gcc -o sdl01 sdl01.o `pkg-config  --cflags  --libs sdl` -lSDL_image  -lSDL_ttf
sdl02:
	gcc  -c sdl02.c 
	gcc -o sdl02 sdl02.o `pkg-config  --cflags  --libs sdl` -lSDL_image  -lSDL_ttf

cannot open shared object file:
	# cannot open shared object file: No such file or directory
	# /usr/local/lib is normally not searched by the dynamic linker. Add it to LD_LIBRARY_PATH.
	# Alternatively, configure the dynamic linker to always search /usr/local/lib and perhaps /usr/local/lib64. 
	# This is usually done by adding the paths to the /etc/ld.so.conf file, and running ldconfig.
	# There is sometimes also a 32/64 bit issue, that is, one tries to run a 32-bit executable and only 64-bit libraries are present, 
	# or vice versa. Run file <somtething>.so and file <your-executable> to determine their architecture. 
	# In general, 32-bit libraries go to <whatever>/lib and 64-bit ones to <whatever>/lib64, but sometimes they end up in a wrong place.

	# export LD_LIBRARY_PATH=$PATH:/usr/local/lib	
	#  g++  main.o -o main -L/usr/local/lib -lxxx
	# sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/usrlocal'  
        # sudo ldconfig
	# after make install, don't forget   sudo ldconfig
	# vi /etc/ld.so.conf
sfml: 
	g++ -c sfml.cpp
	g++ -o sfml sfml.o -lsfml-graphics -lsfml-window -lsfml-system
	#g++ -o sfml sfml.o -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system

clean :
	rm -f *.o
	rm -f hello-xlib
	rm -f hello-cairo
	rm -f glib
	rm -f dfb02
	rm -f gtk0
	rm -f gtk1
	rm -f gl
	rm -f sdl
	rm -f dfb01
	rm -f sdl01
	rm -f sdl02
	rm -f sfml
