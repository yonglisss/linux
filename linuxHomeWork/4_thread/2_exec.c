#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	char *const envp[] = {"USER=liu", "PATH=/tmp", NULL};
	char *argv[] = {"env", NULL};
	pid_t  pid;
	if ((pid = fork()) < 0){
		printf("fork error\n");
		exit(-1);
	}else if (pid == 0){
	if (execve("/bin/env", "env", envp) < 0){
		printf("execve error\n");
		exit(-1);
		}
	}
	if (waitpid(pid, NULL, 0) < 0){
		printf("wait error\n");
		exit(-1);
	}
	return 0;
}
