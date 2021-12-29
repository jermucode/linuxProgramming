#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/utsname.h>
#include <unistd.h>

//This is from the book
	int 
main(int argc, char* argv[])
{
	struct utsname uts;

	if(uname(&uts) == -1)
	{
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);

	}

	printf("Node name: 	%s\n", uts.nodename);
	printf("System name: 	%s\n", uts.sysname);
	printf("Release: 	%s\n", uts.release);
	printf("Version: 	%s\n", uts.version);
	printf("Machine: 	%s\n", uts.machine);
#ifdef _GNU_SOURCE
	printf("Domain name: %s\n", uts.domainname);
#endif
	exit(EXIT_SUCCESS);

}

