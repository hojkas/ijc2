// htab_iterator_get_key.c
// Řešení IJC-DU2, příklad b), 24.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

const char * htab_iterator_get_key(htab_iterator_t it)
{
	char* help = malloc(sizeof(it.ptr->key)+1);
	strcpy(help, it.ptr->key);
	return help;
}