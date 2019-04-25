// tail.c
// Řešení IJC-DU2, příklad a), 15.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_LENGHT 1024 //including \n and \0, real effective value is LINE_LENGHT-2

typedef struct line_t Line;
struct line_t {
	char content[LINE_LENGHT];
	Line *next;
};

//Vytváří jednu strukturu line
Line *create_line()
{
	Line *line = malloc(sizeof(struct line_t));
	if(line == NULL) {
		fprintf(stderr, "tail: allocation fault\n");
		exit(1);
	}
	return line;
}

//Naváže line_to_place na current_line
void add_line(Line *current_line, Line *line_to_place)
{
	current_line->next = line_to_place;
}

//Uvolní lines
void destroy_all_lines(Line *line)
{
	Line* end_line = line;
	Line* next_to_destroy = line->next;
	while(line->next != end_line) {
		next_to_destroy = line->next;
		free(line);
		line = next_to_destroy;
	}
	free(line);
}

//Vytvoří n lines lineárně provázaných
Line *create_lines(unsigned number)
{
	Line* first_line = create_line();
	Line* prev_line = first_line;
	Line* last_line;
	if(number == 1) {
		first_line->next = first_line;
		return first_line;
	}
	for(unsigned i = 1; i < number; i++) {
		last_line = create_line();
		prev_line->next = last_line;
		prev_line = last_line;
	}
	last_line->next = first_line;
	return first_line;
}

//načte zbytek řádku ze stdin, co už se nevejde do LINE_LENGHT
int flush_stdin_line()
{
	int loaded;
	while(1) {
		loaded = fgetc(stdin);
		if(loaded == '\n') return 0;
		if(loaded == EOF) return 1;
	}
}

//načte zbytek řádku z file, co už se nevejde do LINE_LENGHT
int flush_file_line(FILE* file)
{
	int loaded;
	while(1) {
		loaded = fgetc(file);
		if(loaded == '\n') return 0;
		if(loaded == EOF) return 1;
	}
}

/*
* Načte line ze stdin (zbytečně oddělené od load_file_line, lze sloučit)
*/
int load_stdin_line(Line* line, int* overflow_check)
{
	int loaded;
	int found_end = 0;
	int found_eof = 0;
	for(int i = 0; i < LINE_LENGHT - 2 && found_end == 0; i++) {
		loaded = fgetc(stdin);
		if(i == 0 && loaded == EOF) return 2;
		if(loaded != '\n' && loaded != EOF) line->content[i]=loaded;
		else {
			line->content[i] = '\n';
			line->content[i+1] = '\0';
			found_end = 1;
			if(loaded == EOF) found_eof = 1;
		}
	}
	
	if(found_end == 0) {
		line->content[LINE_LENGHT - 2] = '\n';
		line->content[LINE_LENGHT - 1] = '\0';
		if(*overflow_check == 0) fprintf(stderr, "tail: line overflow, chars above %d flushed\n", LINE_LENGHT-2);
		*overflow_check=1;
		found_eof = flush_stdin_line();
	}
	
	return found_eof;
}

/*
* načte line ze souboru
*/
int load_file_line(Line* line, FILE* file, int* overflow_check)
{
	int loaded;
	int found_end = 0;
	int found_eof = 0;
	for(int i = 0; i < LINE_LENGHT - 2 && found_end == 0; i++) {
		loaded = fgetc(file);
		if(i == 0 && loaded == EOF) return 2;
		if(loaded != '\n' && loaded != EOF) line->content[i]=loaded;
		else {
			line->content[i] = '\n';
			line->content[i+1] = '\0';
			found_end = 1;
			if(loaded == EOF) found_eof = 1;
		}
	}
	
	if(found_end == 0) {
		line->content[LINE_LENGHT - 2] = '\n';
		line->content[LINE_LENGHT - 1] = '\0';
		if(*overflow_check == 0) fprintf(stderr, "tail: line overflow, chars above %d flushed\n", LINE_LENGHT-2);
		*overflow_check = 1;
		found_eof = flush_file_line(file);
	}
	
	return found_eof;
}

/*
* Funkce vypíše všechny provázané lines
*/
void write_lines(Line* start_line, unsigned number)
{
	Line* to_write = start_line;
	for (unsigned i = 0; i < number; i++) {
		printf("%s", to_write->content);
		to_write=to_write->next;
	}
}

int main(int argc, char* argv[])
{
	unsigned int row_count = 10;
	unsigned int row_shift = 0;
	char filename[256];
	int do_stdin = 0;
	int shift = 0;
	int end_of_file = 0;
	int overflow_check = 0;
	
	//začátek parsování argumentů
	if(argc > 2 && (strcmp(argv[1], "-n") == 0)) {
		if(argv[2][0] == '+') {
			row_shift = strtol(&argv[2][1], &argv[2], 10);
			shift = 1;
		}
		else if (argv[2][0] == '-') row_count = strtol(&argv[2][1], &argv[2], 10);
		else row_count = strtol(argv[2], &argv[2], 10);
		
		if(argv[2][0] != '\0' || (row_shift == 0 && shift == 1)) {
			fprintf(stderr,"tail: Invalid argument\n");
			exit(1);
		}
		if(row_count == 0) exit(0);
		
		if(argc > 4) {
			fprintf(stderr,"tail: Invalid number of arguments\n");
			exit(1);
		}
		else if(argc == 3) do_stdin = 1;
		else strcpy(filename, argv[3]); //argc = 4
	}
	else if (argc > 2) {
		fprintf(stderr,"tail: Invalid number of arguments\n");
		exit(1);
	}
	else { //not n param
		if(argc == 2) strcpy(filename, argv[1]);
		else if (argc == 1) do_stdin = 1;
	} //hotové parsování argumentů
	
	FILE* f;
	if(do_stdin == 0) {
		f = fopen (filename, "r");
		if(f == NULL) {
			fprintf(stderr, "tail: file could not be opened or wrong format of arguments\n");
			exit(1);
		}
	}

	if(shift == 0) { // -n no + or no -n at all
		Line* current_line = create_lines(row_count);
		while(end_of_file == 0) { //načítá lines ze souboru do kruhu lines, nové přepisují ty staré
			if (do_stdin != 0) end_of_file = load_stdin_line(current_line, &overflow_check);
			else end_of_file = load_file_line(current_line, f, &overflow_check);
			if(end_of_file != 2) current_line = current_line->next;
		}
		write_lines(current_line, row_count);
		destroy_all_lines(current_line);
	}
	else {
		Line* current_line = create_line();
		for(unsigned int i = 1; end_of_file == 0; i++) { //nacte jedinou line, je-li i vetsi nez shift, vypise ji
			if (do_stdin != 0) end_of_file = load_stdin_line(current_line, &overflow_check);
			else end_of_file = load_file_line(current_line, f, &overflow_check);
			if(i >= row_shift && end_of_file != 2) printf("%s", current_line->content);
		}
		free(current_line);
	}
	
	if(do_stdin == 0) fclose(f);
	return 0;
}