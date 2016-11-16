// printer - Open a user provided file stream and print to stdout one character at a time.

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
	FILE *instream = NULL;
	char *filepath = NULL;

	char *usage = "printer -f <FILEPATH>";

	// Get command line arguments.
	int opt;
	while ( (opt = getopt(argc, argv, "f:")) != -1 ) {
		switch (opt) {
		case 'f':
			filepath = optarg;
			break;
		case '?':
			if (optopt == 'f') {
				printf("%s\n", usage);
				return -1;
			} else {
				printf("%s\n", usage);
				return -1;
			}
			break;
		default:
			break;
		}
	}
	
	// Open the input file stream.
	instream = fopen(filepath, "r");
	if (instream == NULL) {
		perror("fopen()");
		return -1;
	}
	

	// Read characters from instream and print to stdout.
	int c;
	while ( (c = fgetc(instream)) != EOF) {
		fputc(c, stdout);
	}
	
	// Check for erros on the input stream.
	if (ferror(instream)) {
		printf("Error reading from input stream.\n");
	}

	// Determine return code.
	if (fclose(instream) == EOF) {
		perror("fclose()");
		return -1;
	} else {
		return 0;
	}
}
