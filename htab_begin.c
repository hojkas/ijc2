// htab_begin.c
// Řešení IJC-DU2, příklad b)
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htab.h"

/*
* RETURNS iterator pointing to first content OR iterator pointin to NULL in case of empty table*/
htab_iterator_t htab_begin(const htab_t * t)
{
	htab_iterator_t it;
	for(unsigned i = 0; i < t->arr_size; i++) {
		if(t->htab_bucket[i] != NULL) {
			it.ptr = t->htab_bucket[i];
			it.t = t;
			it.idx = i;
			return it;
		}
	}
	it.ptr = NULL;
	return it;
}