// htab_size.c
// Řešení IJC-DU2, příklad b)
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htab.h"

size_t htab_size(const htab_t * t)
{
	return t->size;
}
