// htab_init.c
// Řešení IJC-DU2, příklad b)
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

htab_t *htab_init(size_t n)
{
	htab_t *table;
	table = malloc(sizeof(htab_t)); //alokace tabulky
	
	if(table == NULL) return NULL;
	table->htab_bucket = malloc(sizeof(struct htab_item*)*n); //alokace n ukazatelů na položky tabulky
	if(table->htab_bucket == NULL) {
		free(table);
		return NULL;
	}
	
	table->size = 0;
	table->arr_size = n;
	for(unsigned int i = 0; i < n; i++) table->htab_bucket[i] = NULL;
	return table;
}