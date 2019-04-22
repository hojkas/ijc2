// io.c
// Řešení IJC-DU2, příklad b), 16.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "io.h"

int flush_file_line(FILE* file)
{
	int loaded;
	while(1) {
		loaded = fgetc(file);
		if(loaded == EOF) return 1;
		if(isspace(loaded)) return 0;
	}
}

int get_word(char *s, int max, FILE *f)
{
	int loaded;
	int found_end = 0;
	int i;
	
	for(i = 0; i < max - 1 && found_end == 0; i++) {
		loaded = fgetc(f);
		if(loaded == EOF) {
			s[i] = '\0';
			found_end = -1;
		}
		else if(isspace(loaded) && i != 0) {
			s[i] = '\0';
			found_end = 1;
		}
		else if(isspace(loaded) && i == 0) i--;
		else s[i] = loaded;
	} //in i is number of loaded characters, including the \0 char
	
	if(found_end == -1) return EOF;
	else if(found_end == 0) {
		flush_file_line(f);
		s[i] = '\0';
		return i;
	}
	else return i-1;
}