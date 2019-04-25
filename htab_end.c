// htab_end.c
// Řešení IJC-DU2, příklad b), 24.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

htab_iterator_t htab_end(const htab_t * t)
{
	htab_iterator_t it;
	it.t = t;
	it.idx = t->arr_size;
	it.ptr = t->htab_bucket[t->arr_size+1];
	return it;
}