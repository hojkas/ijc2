# Makefile
# Řešení IJC-DU2, 10.4.2019
# Autor: Iveta Strnadová (xstrna14), FIT

SHELL = /bin/bash

CC = gcc
LIBFILE = htab_size.o htab_move.o htab_lookup_add.o htab_iterator_set_value.o htab_iterator_get_value.o htab_iterator_get_key.o htab_iterator_next.o htab_init.o htab_hash_function.o htab_free.o htab_end.o htab_clear.o htab_bucket_count.o htab_begin.o htab.h htab.o
CFLAGS = -std=c99 -Wall -Wextra -pedantic

CPPFLAGS = -std=c++11 -pedantic -Wall

all: tail wordcount tail2 wc-
quick: tail2
	./tail2
	rm tail2

tail: tail.o
	$(CC) $(CFLAGS) tail.o -o tail
tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c -o tail.o
tail2:
	g++ $(CPPFLAGS) tail2.cc -o tail2
	
try: try.o io.o
	$(CC) $(CFLAGS) try.o io.o -o try
io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c -o io.o
try.o: try.c
	$(CC) $(CFLAGS) -c try.c -o try.o

wc-:
	g++ $(CPPFLAGS) -O2 wordcount-.cc -o wc-
	
wordcount: wordcount.o io.o libhtable.a
	$(CC) $(CFLAGS) wordcount.o io.o libhtable.a -o wordcount
wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c wordcount.c -o wordcount.o

#stat.knihovna
libhtable.a: $(LIBFILE)
	ar rcs libhtable.a $(LIBFILE)
	
#soubory pro knihovnu
htab_size.o:
	$(CC) -c htab_size.c -o htab_size.o
htab_move.o:
	$(CC) -c htab_move.c -o htab_move.o
htab_lookup_add.o:
	$(CC) -c htab_lookup_add.c -o htab_lookup_add.o
htab_iterator_set_value.o:
	$(CC) -c htab_iterator_set_value.c -o htab_iterator_set_value.o
htab_iterator_get_value.o:
	$(CC) -c htab_iterator_get_value.c -o htab_iterator_get_value.o
htab_iterator_get_key.o:
	$(CC) -c htab_iterator_get_key.c -o htab_iterator_get_key.o
htab_iterator_next.o:
	$(CC) -c htab_iterator_next.c -o htab_iterator_next.o
htab_init.o:
	$(CC) -c htab_init.c -o htab_init.o
htab_hash_function.o:
	$(CC) -c htab_hash_function.c -o htab_hash_function.o
htab_free.o:
	$(CC) -c htab_free.c -o htab_free.o
htab_end.o:
	$(CC) -c htab_end.c -o htab_end.o
htab_clear.o:
	$(CC) -c htab_clear.c -o htab_clear.o
htab_bucket_count.o:
	$(CC) -c htab_bucket_count.c -o htab_bucket_count.o
htab_begin.o:
	$(CC) -c htab_begin.c -o htab_begin.o
htab.o:
	$(CC) -c htab.c -o htab.o
	
#cleaning
clean:
	rm tail wordcount wc-
massclean:
	rm tail wordcount wc- *.o libhtable.a
