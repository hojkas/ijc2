// io.h
// Řešení IJC-DU2, příklad b), 16.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_word(char *s, int max, FILE *f);

#endif //IO_H