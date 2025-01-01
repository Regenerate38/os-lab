#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	pid_t child_pid;
	child_pid = fork();
	if (child_pid < 0) {
		printf("Fork failed");
		return 1;
	}
	else if (child_pid == 0) {
		printf("child process created\n");
		printf ("child_PID = %d,parent_PID = %d\n", getpid(), getppid());
	}
	else {
		wait(NULL);
		printf ("parent process created!\n");
      		printf ("child_PID = %d, parent_PID = %d\n", getpid( ), getppid( ) );
	}
	return 0;

}
