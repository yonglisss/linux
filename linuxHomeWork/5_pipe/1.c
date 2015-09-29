#include<stdio.h>
#include<unistd.h>

int main(int argc,char * argv[])
{
	int f_des1[2];
	int f_des2[2];

	int pid;
	char msg[BUFSIZ];
	char p_msg[BUFSIZ];

	if(argc != 2)
	{
		printf("数组不够\n");
		return 1;
	}

	if(pipe(f_des1) == -1)
	{
		printf("创建第一个管道失败！\n");
		return 1;
	}

	if(pipe(f_des2) == -1)
	{
		printf("创建第二个管道失败！\n");
		return 1;
	}

	pid = fork();
	if(pid == -1)
	{
		perror("cannot create new process\n");
		return 1;
	}
	else if(pid == 0)
	{
		close(f_des1[1]);
		close(f_des2[0]);
		
		if(read(f_des1[0],msg,BUFSIZ) == -1)
		{
			perror("child process cannot read data from pipe\n");
			return 1;
		}else
			printf("in child process, receive message: %s \n",msg);

		if(write(f_des2[1],msg,strlen(msg)) == -1)
		{
			perror("child process cannot write data to pipe");
			return 1;
		}else
			printf("in child process,send message back: %s \n",argv[1]);
		
		_exit(0);
	}else
	{
		close(f_des1[0]);
		close(f_des2[1]);

		if(write(f_des1[1],argv[1],strlen(argv[1])) == -1)
		{
			perror("parent process cannot write data from pipe");
			return 1;
		}else
			printf("in parent process, send message: %s \n",argv[1]);

		if(read(f_des2[0],p_msg,BUFSIZ) == -1)
		{
			perror("parent process cannot read data from pipe");
			return 1;
		}else
			printf("in parent process, receive message: %s \n",p_msg);

		wait(NULL);
		_exit(0);
	}

	return 0;
}
