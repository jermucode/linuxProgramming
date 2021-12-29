/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
*/
#include "/lib/tlpi_hdr.h"


void errMsg(const char * format , ...);
void errExit(const char * format , ...);
void err_exit(const char * format , ...);
void errExitEN(int errnum , const char * format , ...);

void fatal(const char * format , ...);
void usageErr(const char * format , ...);
void cmdLineErr(const char * format , ...);

int getInt(const char * arg , int flags , const char * name );
long getLong(const char * arg , int flags , const char * name );



int main(void)
{
	FILE *fp = fopen("no_text.txt","r");
	if(fp == NULL)
	{
		perror("fopen");
		printf("%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
}
