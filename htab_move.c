// htab_move.c
// Řešení IJC-DU2, příklad b), 24.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

htab_t *htab_move(size_t n, htab_t *from)
{
	htab_t *table;
	table = htab_init(n);
	if(table == NULL) return NULL;
	int value;
	char* key;
	
	htab_iterator_t curr = htab_begin(from);
	while(curr.ptr != NULL) {
		key = htab_iterator_get_key(curr);
		value = htab_iterator_get_value(curr);
		for(int i = 0; i < value; i++)
			htab_lookup_add(table, key);
		curr = htab_iterator_next(curr);
	}
	htab_clear(from);
}
