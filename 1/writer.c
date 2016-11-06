/* Writer.c - Takes input via stdin and writes to a supplied file. */

#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

#define BUF_SIZE 8 

int main(int argc, char *argv[])
{
	char *buf = malloc(sizeof(char) * BUF_SIZE);
	if (buf == NULL) {
		return -1;
	}
	memset(buf, 0, BUF_SIZE);

	if (argc != 2) {
		return -1;
	}

	int outfd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (outfd == -1) {
		perror("Open():");
		return -1;
	}

	ssize_t ret;
	while ( (ret = read(0, buf, BUF_SIZE)) ) {
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			} else {
				perror("Read():");
				break;
			}
		} else {
			ret = write(outfd, buf, BUF_SIZE);
			if (ret == -1) {
				perror("Write():");
			}
			memset(buf, 0, BUF_SIZE);
		}
	}
	
	if (close(outfd) == -1) {
		perror("Close():");
	}
		
	return 0;
}
