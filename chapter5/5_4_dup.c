#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
/*#include "/lib/tlpi_hdr.h"*/
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>


#define _FILE_OFFSET_BITS 64
#ifndef BUF_SIZE
#define BUF_SIZE 1
#endif

/* 
 * Implement dup and dup2 using 
 * dup() and dup2() using fcntl() and close(), if necessary
 * Can ignore that dup2 and fcntl return different errno values for
 * some error cases. For dup2(), 
 * remember to handle the special case where oldfd equals newfd. 
 * In this case, you should check
 * whether oldfd is valid, which can be done by, for example,
 * checking if fcntl(oldfd, F_GETFL) succeesds. If oldfd is not valid
 * then the function should return -1 with errno set to EBADF.
 * */

int main(int argc, char *argv[])
{



	int fd, fd_dup, fd_dup2, fd_dup3, openFlags; /*Create file and initialize flags */
	mode_t filePerms; /* file permissions*/
	openFlags = O_RDWR | O_CREAT | O_APPEND;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	fd = open("file1",openFlags, filePerms);
	if(fd == -1)
	{
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("Successfully opened fd\n");
	/* This is to test if closing fd makes duplication fail*/
	/* close(fd); It fails*/


	fd_dup = fcntl(0, F_DUPFD);
	if(fd_dup == -1)
	{
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("Successfully duplicated fd into 1\n");

	/* dup2 into a given descriptor*/
	fd_dup2 = fcntl(0, F_DUPFD, 2);
	if(fd_dup2 == -1)
	{
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	/*  Print results of F_GETFD*/
	printf("%d\n", fcntl(2, F_GETFD));

	printf("successfully duplicated fd into 2\n");
	/* dup3 == fd*/
	/* It looks like this works with or without closing fd here
	close(fd);
	*/

	fd_dup3 = fcntl(0, F_DUPFD, 0);
	close(fd);
	if(fd_dup3 == -1)
	{
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);

	}
	/*  Print results of F_GETFD*/
	printf("%ld\n", fcntl(0, F_GETFD));

	printf("successfully duplicated dup_f3 into 0\n");
	exit(EXIT_SUCCESS);
}
