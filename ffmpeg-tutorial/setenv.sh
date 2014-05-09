#!/bin/sh

DIR=$PWD
echo DIR=$DIR
echo HOME=$HOME
echo MY_ROOT=$MY_ROOT
echo LD_CONFIG_PATH=$LD_CONFIG_PATH
echo PKG_CONFIG_PATH=$PKG_CONFIG_PATH
echo ===================================

if [ -z "$MY_ROOT" ]; then
	export MY_ROOT=/home/wj/My/ffmpeg-tutorial
fi

if [ -z "$MY_PATH_DEFINED" ]; then
	export PATH=$MY_ROOT:$MY_ROOT/bin:$PATH
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
	export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$HOME/ffmpeg_build/lib/pkgconfig
	export MY_PATH_DEFINED=1
fi	

echo MY_ROOT=$MY_ROOT
echo PKG_CONFIG_PATH=$PKG_CONFIG_PATH
echo LD_CONFIG_PATH=$LD_CONFIG_PATH
echo ====================================


