#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void main()
{
	int pid;
	pid=fork();
	if (pid==0)
	{
		printf("\n Child Process\n");
		printf("\n Child Process id is %d",getpid());
		printf("\n Its parent process id is %d",getppid());
		sleep(5);

		printf("Child process after sleep=5\n");
		printf("\n Child Process id is %d ",getpid());
		printf("\n Its parent process id is %d",getppid());
	}
	else
	{
		printf("\nParent process");
		sleep(10);
		printf("\n Child Process id is %d ",getpid());
		printf("\n Its parent process id is %d",getppid());
		printf("\nParent terminates\n");
	}
}
