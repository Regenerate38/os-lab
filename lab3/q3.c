#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
	int id=fork();
	if(id==-1)
	{
		printf("cannot create the file");
		exit(1);
	}
	else if(id==0)
	{
		sleep(2);
		printf("this is child process");
	}
	else
	{
		printf("parent process");
		exit(1);
	}
}
