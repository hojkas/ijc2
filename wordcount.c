// wordcount.c
// Řešení IJC-DU2, příklad b), 25.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include <stdio.h>
#include <stdlib.h>
#include "htabp.h"
#include "io.h"

#define MAX_LENGHT 1024
#define TAB_SIZE 50

int main()
{	
	//init of hash table
	htab_t* table;
	table = htab_init(TAB_SIZE);
	if(table == NULL) {
		fprintf(stderr, "Error in allocating memory for table\n");
		exit(1);
	}
	
	htab_iterator_t iterator;
	
	char word[MAX_LENGHT];
	int loaded;
	int overflow = 0;
	loaded = get_word(word, MAX_LENGHT, stdin);
	if(loaded == MAX_LENGHT) {
		fprintf(stderr, "Warning: First line longer than limit reached, some words will be shortened\n");
		overflow = 1;
	}
	
	
	//loading words into hash table
	while(loaded != EOF) {
		iterator = htab_lookup_add(table, word);
		if(iterator.ptr == NULL) {
			fprintf(stderr, "Error in alocating content of table\n");
			htab_free(table);
			exit(1);
		}
		loaded = get_word(word, MAX_LENGHT, stdin);
		if(loaded == MAX_LENGHT && overflow == 0) {
			fprintf(stderr, "Warning, first line longer than limit reached, some words will be shortened\n");
			overflow = 1;
		}
	}
	
	//going through hash table content and printing the words with count
	htab_iterator_t curr = htab_begin(table);
	while(curr.ptr != NULL) {
		printf("%s          %d\n", curr.ptr->key, curr.ptr->data);
		curr = htab_iterator_next(curr);
	}
	
	htab_free(table);
	return 0;
}