#! /usr/bin/env bash

export LD_LIBRARY_PATH=/home/qihangkong/usr/lib
export LIBGL_ALWAYS_SOFTWARE=1
export GALLIUM_DRIVER=swr

g++  test.cpp -lGL -lGLU -lglut -I/home/qihangkong/usr/include -L/home/qihangkong/usr/lib -g

./a.out
