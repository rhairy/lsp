/* rnp.c - Read up to 255 characters from a file and print it to stdout. */

#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

#define BUF_SIZE 256
#define BUF_READ 64

int main(int argc, char *argv[])
{
	char *buf = malloc( sizeof(char) * BUF_SIZE );
	if (buf == NULL) {
		return -1;
	}

	if (argc != 2) {
		return -1;
	}
	
	int fd = open(argv[1], O_RDONLY);

	if (fd == -1) {
		perror("Open():");
		return -1;
	}

	ssize_t bytes_read = 0;
	ssize_t len = BUF_SIZE - 1;

	while ( len != 0 && (bytes_read = read(fd, buf, len)) ) {
		len -= bytes_read;
		buf += bytes_read;
	}
	*buf = '\0';
	buf -= bytes_read;

	
	return 0;

}
