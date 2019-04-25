// htab_iterator_get_value.c
// Řešení IJC-DU2, příklad b), 24.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

int htab_iterator_get_value(htab_iterator_t it)
{
	return it.ptr->data;
}