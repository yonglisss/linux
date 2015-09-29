#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc,char *argv[] )
{
	int i;
	pid_t pid1,pid2,pid3;
	int stat_val;
	char *envp[] = {"PATH = .",NULL};    

	if (argc < 4){
		printf("argc error\n");
		exit(-1);
	}

	for(i = 1;i<4;i++){
		if(strcmp("a",argv[i]) == 0){
			pid1 = fork();
			if(pid1 == 0)
			{
				execve("a",argv,envp);
				return 0;
			}
		}
		if(strcmp("b",argv[i]) == 0){
			pid2 = fork();
			if(pid2 == 0)
			{
				execve("b",argv,envp);
				return 0;
			}
		}
		if(strcmp("c",argv[i]) == 0){
			pid3 = fork();
			if(pid3 == 0)
			{
				execve("c",argv,envp);
				return 0;
			}
		}

	}
	wait(&stat_val);
	wait(&stat_val);
	wait(&stat_val);
	return 0;
}
