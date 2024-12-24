#!/bin/bash

KLEE="/home/karina/bootstrap/klee/include"
FILENAME=$1
cd entertainment/$FILENAME
clang -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone -I ${KLEE} $FILENAME.c
klee --libc=uclibc $FILENAME.bc
cd ../../