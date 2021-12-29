


/*
5-1. Modify the program in Listing 5-3 to use standard file I/O system calls (open() and
lseek()) and the off_t data type. Compile the program with the _FILE_OFFSET_BITS
macro set to 64, and test it to show that a large file can be successfully created.
*/
/* gcc to largefile */
#define _FILE_OFFSET_BITS 64


#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "/lib/tlpi_hdr.h"
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	off_t off;
	if(argc != 3 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s pathname offset\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	off = atoll(argv[2]);
	if(lseek(fd, off, SEEK_SET) == -1)
	{
		printf("lseek\n");
		exit(EXIT_FAILURE);
	}
	if(write(fd, "test", 4) == -1)
	{
		printf("write\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}


