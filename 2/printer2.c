/* printer2 - Read from a file and print to standard output using stdio fgets. */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(int argc, char* argv[])
{
	char *usage = "printer2 <FILEPATH>";
	
	char *buf = malloc(sizeof(char) * BUF_SIZE);
	if (buf == NULL) {
		printf("malloc(): ERROR\n");
		return -1;
	}

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

	while (fgets(buf, BUF_SIZE, infile) != NULL) {
		fputs(buf, stdout);
	}	

	if (ferror(infile)) {
		perror("");
	}
	
	if (fclose(infile) == EOF) {
		perror("fclose():");
		return -1;
	}

	free(buf);
	buf = NULL;

	return 0;	
}
