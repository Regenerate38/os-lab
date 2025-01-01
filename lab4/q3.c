#include <stdio.h>
#include <stdlib.h>

void main()
{
	int id;
	if(id=create("file.txt",0)==-1)
	{
		printf("cannot create file");
		exit(1);
	}
	else
	{
		printf("file is successfuly created");
		exit(1);
	}
}
