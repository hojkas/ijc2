# Makefile
# Řešení IJC-DU2, 10.4.2019
# Autor: Iveta Strnadová (xstrna14), FIT

SHELL = /bin/bash

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic

CPPFLAGS = -std=c++11 -pedantic -Wall

all: tail

ott: otterly.c
	$(CC) $(CFLAGS) otterly.c -o ott

tail: tail.o
	$(CC) $(CFLAGS) tail.o -o tail
tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c -o tail.o
tail2:
	g++ $(CPPFLAGS) tail2.cc -o mytail2
	
try: try.o io.o
	$(CC) $(CFLAGS) try.o io.o -o try
io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c -o io.o
try.o: try.c
	$(CC) $(CFLAGS) -c try.c -o try.o

wc-:
	g++ $(CPPFLAGS) -O2 wordcount-.cc -o wc-
