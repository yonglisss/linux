#include <stdio.h>

int main()
{
	int i = 0;
	long sum  = 1;
	
	for (i = 1; i <= 10; i++){
		sum *= i;
	}
	printf("10! = %ld\n",sum);
	return (0);
}

