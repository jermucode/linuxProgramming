#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "/lib/tlpi_hdr.h"
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif


int main(int argc, char *argv[])
{
	int fd, openFlags;
	mode_t filePerms;
	openFlags = O_CREAT | O_WRONLY | O_APPEND;
	filePerms = S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH;
	ssize_t numRead;
	char buf[BUF_SIZE];
	char *text1 = "First line of text\n";
	char *text2 = "Second text to be appended\n";
	char *text3 = "Third input to be put after SEEK_SET\n";




	fd = open("writehere", openFlags, filePerms);
	if(fd == -1)
	{
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	/* Write text1 into the output file*/
	write(fd, text1, strlen(text1));

	/* Write text2 into the output file, this should get appended*/
	write(fd, text2, strlen(text2));

	/*SEEK_SET fd pointer and write. Where does the text wind up at?*/
	lseek(fd, 0, SEEK_SET);
	write(fd, text3, strlen(text3));
	

	exit(EXIT_SUCCESS);
}









