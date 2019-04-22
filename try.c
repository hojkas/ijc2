#include<stdio.h>
#include<string.h>
#include "io.h"

int main()
{
	char string[20];
	FILE* f = fopen("soubor", "r");
	int lenght = 0;
	
	while (lenght != EOF) {
		printf("Got here");
		lenght = get_word(string,20,f);
		if(lenght != EOF) printf("Word: %s\nLenght: %d\n--\n", string, lenght);
	}
	
	return 0;
}
