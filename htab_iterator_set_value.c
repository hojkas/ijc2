// htab_iterator_set_value.c
// Řešení IJC-DU2, příklad b)
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

int htab_iterator_set_value(htab_iterator_t it, int val)
{
	if(it.ptr == NULL) return 1;
	it.ptr->data = val;
	return 0;
}