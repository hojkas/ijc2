// htab_lookup_add.c
// Řešení IJC-DU2, příklad b)
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "htab.h"
#include <stdio.h>

struct htab_item* create_item(const char* key)
{
	struct htab_item *item;
	item = malloc(sizeof(struct htab_item));
	if(item == NULL) return NULL;
	char* help = malloc(sizeof(key)+1);
	if(help == NULL) {
		free(item);
		return NULL;
	}
	strcpy(help, key);
	item->key = help;
	item->data = 0;
	item->next = NULL;
	return item;
}

htab_iterator_t htab_lookup_add(htab_t * t, const char *key)
{
	htab_iterator_t result;
	unsigned int hash = htab_hash_function(key) % (t->arr_size);
	int found = 0;
	result.t = t;
	result.idx = hash;

	if(t->htab_bucket[hash] == NULL) {
		struct htab_item *item;
		item = create_item(key);
		if(item == NULL) {
				result.ptr = NULL;
				return result;
		}
		t->htab_bucket[hash] = item;
		t->size++;
		result.ptr = item;
		result.ptr->data++;
		return result;
	}
	else {
		struct htab_item *curr_item = t->htab_bucket[hash];
		if(strcmp(key, curr_item->key) == 0) found = 1;
		while(curr_item->next != NULL && found == 0) {
			curr_item=curr_item->next;
			if(strcmp(key, curr_item->key) == 0) found = 1;
		}
		if(found == 1) result.ptr = curr_item;
		else {
			struct htab_item *new_item;
			new_item = create_item(key);
			if(new_item == NULL) {
				result.ptr = NULL;
				return result;
			}
			curr_item->next = new_item;
			t->size++;
			result.ptr = new_item;
		}
	}
	result.ptr->data++;
	return result;
}