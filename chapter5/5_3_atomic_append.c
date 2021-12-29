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

int main(int argc, char *argv[])
{
	int fd, openFlags; /*Create file and initialize flags */
	int opt, xfnd; /* command-line options*/
	mode_t filePerms; /* file permissions*/
	xfnd = 0; /* set x command line option to zero*/
	off_t off, i; /* Initialize offset for filesize */
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	/*char buf[BUF_SIZE];*/


	if(argc == 1 || argc == 2 || strcmp(argv[1], "--help") == 0)
	{

		printf("program needs at least 2 arguments\n");
		exit(EXIT_FAILURE);

	}

	off = atoll(argv[optind+1]);

	/* Command line options arguments*/

	while((opt = getopt(argc, argv, ":x")) != -1)
	{

		switch(opt)
		{
			case 'x':
				xfnd++;
				break;
			default: 
				xfnd = 0;



		}

	}

	/* From command line arguments we deduce appending or not*/
	if(xfnd != 0)
	{
		openFlags = O_RDWR | O_CREAT;
		fd = open(argv[optind], openFlags, filePerms);
		if(fd == -1)
		{
			printf("%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}


		for(i = 0; i < off; i++)
		{

			lseek(fd, 0, SEEK_END);

			if(write(fd, "a", 1) == -1)
			{

				printf("could not write in xfnd loop\n");
				exit(EXIT_FAILURE);
			}
		}



	}


	else
	{
		openFlags =O_RDWR | O_CREAT | O_APPEND;
		fd = open(argv[optind], openFlags, filePerms);
		if(fd == -1)
		{

			printf("%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		for(i = 0; i < off; i++)
		{
			if(write(fd, "a", 1) == -1)
			{

				printf("could not write in default loop\n");
				exit(EXIT_FAILURE);
			}

		}


	}




	exit(EXIT_SUCCESS);










}
