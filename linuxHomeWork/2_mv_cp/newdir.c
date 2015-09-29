#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
//	int fd1,fd2;
//	char buffer[100];
	int num;

	if(mkdir("./aaa_newdir",0111) == -1)
	{
		perror("Cannot creat directory");
		return 1;
	}

	return 0;
}
