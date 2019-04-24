// tail2.cc
// Řešení IJC-DU2, příklad a), 15.4.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: g++ 7.3.0

#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>

using namespace std;

int main (int argc, char* argv[])
{
	unsigned int row_count = 10;
	unsigned int row_shift = 0;
	string filename;
	int do_stdin = 0;
	int shift = 0;
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
	
	queue<string> lines;
	string help_string;
	
	if(do_stdin == 1) {
		if(shift == 0) {
			while(1) {
				if(cin.eof()) break;
				getline(cin, help_string);
				cin >> help_string;
				if(help_string.empty() == 0) lines.push(help_string);
				if(lines.size() > row_count) lines.pop();
			}
			while(lines.size() > 0) {
				cout << lines.front() << endl;
				lines.pop();
			}
		}
		else {
			for(unsigned i = 0; cin.eof() == 0; i++) {
					cin >> help_string;
					if(i + 2 > row_shift) cout << help_string << endl;
			}
		}
	}
	else {
		ifstream file;
		file.open(filename, ios::in);
		if(file.is_open() == 0) {
			cerr << "tail: file could not be opened or wrong format of arguments" << endl;
			exit(1);
		}
		
		if(shift == 0) {
			while(1) {
				if(file.eof()) break;
				getline(file,help_string);
				if(help_string.empty() == 0) lines.push(help_string);
				if(lines.size() > row_count) lines.pop();
			}
			while(lines.size() > 0) {
				cout << lines.front() << endl;
				lines.pop();
			}
		}
		else {
			for(unsigned i = 0; file.eof() == 0; i++) {
					file >> help_string;
					if(i + 2 > row_shift) cout << help_string << endl;
			}
		}
		
		file.close();
	}
	
	
	
	return 0;
}