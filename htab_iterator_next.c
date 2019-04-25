// htab_iterator_next.c
// Řešení IJC-DU2, příklad b), 24.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

/**
* returns next iterator OR iterator pointing to null in case of end of table */
htab_iterator_t htab_iterator_next(htab_iterator_t it)
{
	if(it.ptr->next != NULL) {
		it.ptr = it.ptr->next;
		return it;
	}
	
	for(unsigned i = it.idx + 1; i < it.t->arr_size; i++)
		if(it.t->htab_bucket[i] != NULL) {
			it.idx = i;
			it.ptr = it.t->htab_bucket[i];
			return it;
		}
		
	it.ptr = NULL;
	return it;
}
