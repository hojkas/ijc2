// htab_free.c
// Řešení IJC-DU2, příklad b), 22.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htabp.h"

void htab_free(htab_t * t)
{
	htab_clear(t);
	free(t->htab_bucket);
	free(t);
}