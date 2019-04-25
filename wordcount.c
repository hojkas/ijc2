#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "io.h"

#define MAX_LENGHT 500

int main(int argc, char* argv[])
{
	if(argc != 2) {
		fprintf(stderr, "Wrong number of arguments\n");
		exit(1);
	}
	
	FILE* file;
	file = fopen(argv[1], "r");
	if(file == NULL) {
		fprintf(stderr, "Error in opening given file\n");
		exit(1);
	}
	
	htab_t* table;
	table = htab_init(10);
	if(table == NULL) {
		fprintf(stderr, "Error in allocating memory for table\n");
		fclose(file);
		exit(1);
	}
	
	htab_iterator_t iterator;
	
	char word[MAX_LENGHT];
	int loaded;
	loaded = get_word(word, MAX_LENGHT, file);
	
	while(loaded != EOF) {
		iterator = htab_lookup_add(table, word);
		if(iterator.ptr == NULL) {
			fprintf(stderr, "Error in alocating content of table\n");
			htab_free(table);
			fclose(file);
			exit(1);
		}
		loaded = get_word(word, MAX_LENGHT, file);
	}
	
	htab_iterator_t curr = htab_begin(table);
	while(curr.ptr != NULL) {
		printf("%s - %d\n", curr.ptr->key, curr.ptr->data);
		curr = htab_iterator_next(curr);
	}
	
	fclose(file);
	htab_free(table);
	return 0;
}