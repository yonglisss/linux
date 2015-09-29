#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
	int fd1,fd2;
	char buffer[100];
	int num;
	
	char filename1[10] = "pass";
	char filename2[20] = "/etc/passwd";


	if((fd2 = open(filename2,O_RDONLY)) == -1)
	{
		perror("Cannot open this file");
		return 1;
	}
	if((fd1 = open(filename1,O_CREAT | O_WRONLY,S_IRUSR|S_IWUSR)) == -1)
	{
		perror("Cannot creat that file");
		return 1;
	}
	while((num = read(fd2,buffer,100)) > 0)
	{
		if((write(fd1,buffer,num)) == -1)
		{
			perror("Cannot write this file");
			return 1;
		}
	}

	close(fd1);
	close(fd2);
	return 0;
}
