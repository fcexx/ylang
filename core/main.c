#include <stdint.h>
#include <stdio.h>

int main(int argc, const char ** argv) {
	if (argc == 1) {
		fprintf(stderr, "Usage: %s [flags] file.y\n", argv[0]);
	} else {
		for (int i = 1; i < argc; i++) {
			if (argv[i][0] == '-') printf("flag!\n");
		}
	}
	return 0;
}
