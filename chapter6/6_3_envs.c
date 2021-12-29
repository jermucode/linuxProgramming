#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;


/* Implement setenv() and
 * unsetenv() using getenv(), 
 * putenv() and where necessary, 
 * code that directly modifies environ.
 *
 * unsetenv() should check to see
 * whether there are multiple definitions of
 * an environment variable
 * and remove them all*/

/* This is setenv*/
int envsetter(char *name, char *value, int overwrite)
{
	/* initialize lengths*/
	size_t lenName, lenValue; 
	lenName = strlen(name);
	/* Malloc the variables,
	 * this is needed for strcat*/
	char *env = malloc((((int) lenName) + 1) * sizeof(char));
	env = name;

	/* This is the same as above*/	
	lenValue = strlen(value);
	char *val = malloc((((int) lenValue) + 1) * sizeof(char));
	val = value;
	/* calloc dest string*/
	char *dest = calloc((int)(lenName + 1 + lenValue + 1),  sizeof(char));

	/*strcat everything */	
	strcat(dest, env);
	strcat(dest, "=");
	strcat(dest, val);

	/* This is used to set env*/
	char *getenver = malloc(((int) lenName +1) * sizeof(char));

	/* we will modify returnvalue
	 * instead of checking for EXIT_FAILURE*/	
	int returnvalue = 1;

	/* Check overwrite condition*/
	if(overwrite == 0)
	{
		getenver = getenv(name);
		//printf("%s\n", getenver);
		if(getenver == NULL)
		{
			if(putenv(dest) != 0)
				returnvalue = 0;
		}
	}
	else
	{
		if(putenv(dest) != 0)
			returnvalue = 0;
	}

	/* Everything is fine*/
	
	return returnvalue;

}
int unsetter(char *name)
{
	size_t lenName;
	lenName = strlen(name);
	char *getenver = malloc(((int) lenName + 1) * sizeof(char));
	int returnvalue = 1;
	char **ep;

	



	if(getenv(name) != NULL)
	{
		getenver = getenv(name);
		printf("%s\n", getenver);
		char *dest = calloc((int) lenName + 1 + (int) strlen(getenver) + 1, sizeof(char));
		strcat(dest, name);
		strcat(dest, "=");
		strcat(dest, getenver);
		for(ep = environ; *ep != NULL; ep++)
		{
			//printf("%s\n", *ep);
			//printf("%s\n", dest);
			
			if(strcmp(dest, *ep) == 0)
			{
				printf("in unsetter if\n");
				printf("%s\n", *ep);
				printf("%s\n", dest);


			}
			


		}


	}
return 1;

}



int main(int argc, char *argv[])
{
	char *nam = "EDITOR";
	char *value = "nano";
	int retval;

	/* modify overwrite
	 * when calling envsetter*/
	
	int overwrite = 1;

	retval = envsetter(nam, value, overwrite);
	char *ep = malloc(20*sizeof(char));
	ep = getenv("EDITOR");
	printf("%s\n", ep);
	printf("setenv returned: %d\n", retval);

	retval = unsetter(nam);



	exit(EXIT_SUCCESS);

}



