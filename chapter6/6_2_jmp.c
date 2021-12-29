#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

int returnjump(int val)
{
	printf("called into returnjump\n");
	printf("in setjump %d\n",val*2);
	setjmp(env);
	return val;
	

	
}


int main(int argc, char *argv[])
{
	int val1 = 5;
	int val2 = 10;
	int returnme=0;
	/*
	if(val1 == 5)
	{

		returnme=returnjump(val1);
		setjmp(env);
		printf("%d\n", returnme);

		
	}
	*/
	if(val2 == 10)
	{
		returnme=returnjump(val2);
		longjmp(env, 1);
		printf("%d\n", returnme);
	}

exit(EXIT_SUCCESS);








}

