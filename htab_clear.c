// htab_clear.c
// Řešení IJC-DU2, příklad b)
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

void htab_clear(htab_t * t)
{
	struct htab_item *curr_item;
	struct htab_item *last_item;
	for(unsigned i = 0; i < t->arr_size; i++) {
		if(t->htab_bucket[i] == NULL) continue;
		curr_item = t->htab_bucket[i];
		while(curr_item->next != NULL) {
			last_item = curr_item;
			curr_item = curr_item->next;
			free(last_item->key);
			free(last_item);
		}
		free(curr_item->key);
		free(curr_item);
		t->htab_bucket[i] = NULL;
	}
}