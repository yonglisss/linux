#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

void my_perror(const char * str)
{
	printf("%s: ", str);
	switch(errno){
		case 1: printf("Operation not permitted\n");
			break;
		case 2: printf("No such file or diretory\n");
			break;
		case 3: printf("No such process\n");
			break;
		case 4: printf("Interrupted system call\n");
			break;
		case 5: printf("I/O error\n");
			break;
		case 6: printf("No such device or address\n");
			break;
		case 7: printf("Arguement list too long\n");
			break;
		case 8: printf("Exec format error\n");
			break;
		case 9: printf("Bad file number\n");
			break;
		case 10: printf("No child process\n");
			break;
		case 11: printf("Try again\n");
			break;
		case 12: printf("Out of memory\n");
			break;
		case 13: printf("Permission denied\n");
			break;
		case 14: printf("Bad address\n");
			break;
		case 15: printf("Block device required\n");
			break;
	}
}