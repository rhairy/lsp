/* printer - Read from a file and print to standard output using stdio. */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	char *usage = "printer <FILEPATH>";

	if (argc != 2) {
		printf("%s\n", usage);
		return -1;
	}
	
	FILE *infile;   

	infile = fopen(argv[1], "r");
	if (infile == NULL) {
		perror("fopen():");
		return -1;
	}

	int c;
	while ( (c = fgetc(infile)) != EOF) {
		fputc(c, stdout);
	}
	if (ferror(infile)) {
		perror("");
	}
	
	if (fclose(infile) == EOF) {
		perror("fclose():");
		return -1;
	}

	return 0;	
}
