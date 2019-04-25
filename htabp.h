#include "htab.h"

//TODO remove from here, just temp
typedef struct {
	size_t size;
	size_t arr_size;
	struct htab_item** htab_bucket;
} htab_t;

//TODO also remove and to it opaque
struct htab_item {
	char* key;
	int data;
	struct htab_item* next;
};