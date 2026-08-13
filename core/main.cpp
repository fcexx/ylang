#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <lexer.hpp>
#include <iostream>

using namespace std;

int parse_flag(string flag) {
	return 8;
}


int main(int argc, const char ** argv) {
	if (argc == 1) {
		fprintf(stderr, "Usage: %s [flags] file.y\n", argv[0]);
	} else {
		for (int i = 1; i < argc; i++) {
			struct stat file;

			if (argv[i][0] == '-') {
				string flag = argv[i];
				if (parse_flag(flag) != 0) {
					fprintf(stderr, "error: unknown flag %s\n", flag);
					exit(2);
				}
				continue;
			}
			if (stat(argv[i], &file) == 0) {
				vector<Token> tok = lexer(argv[i]);
				for (const Token& token : tok) {
					cout << token.value << '\n';
				}

			} else {
				printf("no file\n");
			}
		}
	}
	return 0;
}