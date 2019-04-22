// tail2.cc
// Řešení IJC-DU2, příklad a), 15.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: g++ 7.3.0

#include <iostream>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

int main (int argc, char* argv[])
{
	unsigned int row_count = 10;
	unsigned int row_shift = 0;
	string filename;
	int do_stdin = 0;
	int shift = 0;
	int end_of_file = 0;
	int overflow_check = 0;
	string argv_one;
	if(argc > 1) argv_one = argv[1];
	
	if(argc > 2 && (argv_one.compare("-n")==0)) {
		if(argv[2][0] == '+') {
			row_shift = strtol(&argv[2][1], &argv[2], 10);
			shift = 1;
		}
		else if (argv[2][0] == '-') row_count = strtol(&argv[2][1], &argv[2], 10);
		else row_count = strtol(argv[2], &argv[2], 10);
		
		if(argv[2][0] != '\0' || (row_shift == 0 && shift == 1)) {
			cerr << "tail: Invalid argument" << endl;
			exit(1);
		}
		if(row_count == 0) exit(0);
		
		if(argc > 4) {
			cerr << "tail: Invalid number of arguments" << endl;
			exit(1);
		}
		else if(argc == 3) do_stdin = 1;
		else filename = argv[3]; //argc = 4
	}
	else if (argc > 2) {
		cerr << "tail: Invalid number of arguments" << endl;
		exit(1);
	}
	else { //not n param
		if(argc == 2) filename = argv[1];
		else if (argc == 1) do_stdin = 1;
	} //hotové parsování argumentů
	
	cout << "row_count: " << row_count << endl << "row_shift: " << row_shift << endl << "filename: " << filename << endl;
	
	/*
	FILE* f;
	if(do_stdin == 0) {
		f = fopen (filename, "r");
		if(f == NULL) {
			cerr << "tail: file could not be opened or wrong format of arguments" << endl;
			exit(1);
		}
	}

	if(shift == 0) { // -n no + or no -n at all
		//
		Line* current_line = create_lines(row_count);
		while(end_of_file == 0) {
			if (do_stdin != 0) end_of_file = load_stdin_line(current_line, &overflow_check);
			else end_of_file = load_file_line(current_line, f, &overflow_check);
			if(end_of_file != 2) current_line = current_line->next;
		}
		write_lines(current_line, row_count);
		destroy_all_lines(current_line);
	}
	else {
		Line* current_line = create_line();
		for(unsigned int i = 1; end_of_file == 0; i++) {
			if (do_stdin != 0) end_of_file = load_stdin_line(current_line, &overflow_check);
			else end_of_file = load_file_line(current_line, f, &overflow_check);
			if(i >= row_shift && end_of_file != 2) printf("%s", current_line->content);
		}
		free(current_line);
	}
	
	if(do_stdin == 0) fclose(f);*/
	return 0;
}