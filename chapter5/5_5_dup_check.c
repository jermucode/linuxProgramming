#define _FILE_OFFSET_BITS 64


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


#ifndef BUF_SIZE
#define BUF_SIZE 1
#endif

/* 
 * Write a program to verify that duplicated file
 * descriptors share a file offset value and open file status flags*/

int main(int argc, char *argv[])
{


	int fd, fd_dup, openFlags, i;
	mode_t filePerms; /* file permissions*/
	off_t off; /*Define offset */
	openFlags = O_RDWR | O_CREAT | O_APPEND;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	off=1000; /* We'll just use 1000 bits here*/
	fd = open("file",openFlags, filePerms);
	if(fd == -1)
	{

		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Successfully opened fd\n");
	
	for(i = 0; i < off; i++)
	{
		if(write(fd, "\0", 1) == -1)
		{
			printf("Could not write to file\n");
			exit(EXIT_FAILURE);
		}

	}


	fd_dup = fcntl(fd, F_DUPFD);
	if(fd_dup == -1)
	printf("duplicated fd into 1.\n");
	printf("offset=%lld\n", (long long) off);

	
	/*  Check if file permissions match
	 *  we use a bitwise OR here*/
	printf("fileperms are:\n");
	printf("%d\n", fcntl(0, F_GETFD) | fcntl(1, F_GETFD));
	
	/*  Check that lseeks match*/
	if(lseek(fd, 0, SEEK_END) == lseek(fd_dup, 0, SEEK_END))
	{
		printf("Same offset\n");
		printf("%ld\n", lseek(fd, 0, SEEK_END));
		printf("%ld\n", lseek(fd_dup, 0, SEEK_END));
	}
	else
	{
		printf("Not same offsets\n");
		printf("%ld\n", lseek(fd, 0, SEEK_END));
		lseek(fd_dup, 0, SEEK_SET);
		printf("%ld\n", lseek(fd_dup, 0, SEEK_END));
	}

	exit(EXIT_SUCCESS);






}


