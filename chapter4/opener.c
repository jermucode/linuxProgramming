#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int fd; 
	fd = open("startup", O_RDONLY);
	if(fd == -1)
	{
		printf("%d: %s\n",errno,strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Open new or existing file for reading and writing, 
	 * truncating to zero bytes; file permissions read+write for owner, 
	 * nothing for all other users */

	fd = open("myfile", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		printf("%d: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Open new or existing file for writing; writes should always
	 * append to end of file */

	fd = open("w.log", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 
			S_IRUSR | S_IWUSR);

	if(fd == -1)
	{
		printf("%d: %s\n",errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

}
