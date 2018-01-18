#! /usr/bin/env bash

export LD_LIBRARY_PATH=/home/qihangkong/usr/lib

gcc  test1.cpp -lGL -lGLU -lglut -I/home/qihangkong/usr/include -L/home/qihangkong/usr/lib -g

gdb a.out -q
