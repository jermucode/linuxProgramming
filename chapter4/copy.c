#include <sys/stat.h>
#include <fcntl.h>
#include "/lib/tlpi_hdr.h"

#ifndef BUF_SIZE /*Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

/* Call using: ./copying input.txt out.txt
 * out.txt needs to be provided but empty
 * use touch out.txt to create the outputfile for writing */


int main(int argc, char *argv[])
{
	int inputFd, outputFd, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];

	if(argc != 3 || strcmp(argv[1],"--help") == 0)
	{
		printf("%s\n old-file new-file\n",argv[0]); /*prints ./copying
 old-file new-file */
	}
	
	inputFd = open(argv[1], O_RDONLY);
	if(inputFd == -1)
	{
		printf("opening file %s\n",argv[1]);
		exit(EXIT_FAILURE);
	}

	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	/* rw-rw-rw- */

	outputFd = open(argv[2], openFlags, filePerms);
	if(outputFd == -1)
	{
		printf("opening file %s\n", argv[2]);

	}
	
	/* Transfer data until we encounter enf of input or an error */
	
	while((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
	{
		if(write(outputFd, buf, numRead) != numRead)
		{
			printf("could not write whole buffer\n");
			exit(EXIT_FAILURE);
		}
	}
		if(numRead == -1)
		{
			printf("read\n");
			exit(EXIT_FAILURE);
		}
		if(close(inputFd) == -1)
		{
			printf("close input\n");
			exit(EXIT_FAILURE);
		}
		if(close(outputFd) == -1)
		{
			printf("close output\n");
			exit(EXIT_FAILURE);
		}





	exit(EXIT_SUCCESS);
}
