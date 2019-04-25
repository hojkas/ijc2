// htab_size.c
// Řešení IJC-DU2, příklad b), 24.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

size_t htab_size(const htab_t * t)
{
	return t->size;
}
