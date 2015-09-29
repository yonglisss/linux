/*read返回值的练习*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char * argv[])
{
	int fd;

	char buffer[100];

	int num;

	if(argc != 2)
	{
		printf("the parameter < 2\n");
		return 1;
	}

	if((fd = open(argv[1],O_RDONLY)) == -1)
	{
		perror("opening had error!\n");
		return 1;
	}

	while((num = read(fd,buffer,100)) > 0)
	{
		printf("%d\n",num);
		printf("%s\n",buffer);
	}

	close(fd);
	return 0;
}
