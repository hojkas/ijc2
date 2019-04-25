// htab_iterator_get_key.c
// Řešení IJC-DU2, příklad b)
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

const char * htab_iterator_get_key(htab_iterator_t it)
{
	return it.ptr->key;
}