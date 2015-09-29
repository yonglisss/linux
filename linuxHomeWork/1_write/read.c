/*对应那个write程序，这段代码是读取info.txt文件的
 */

#include<stdio.h>
#include<stdlib.h>

#define N 3

typedef struct Info
{
	char name[10];
	char class[10];
	int grade_a;
	int grade_b;
	int grade_c;
}Info;

void main()
{
	int i;
	FILE *fp;
	Info xinxi[N];
	fp = fopen("info.txt","rt");
	
	for(i = 0; i < N; i++)
	{
		fscanf(fp,"%s %s %d %d %d",xinxi[i].name,xinxi[i].class,&xinxi[i].grade_a,&xinxi[i].grade_b,&xinxi[i].grade_c);
	}
	fclose(fp);

	for(i = 0; i < N; i++)
	{
		printf("%s %s %d %d %d",xinxi[i].name,xinxi[i].class,xinxi[i].grade_a,xinxi[i].grade_b,xinxi[i].grade_c);
		printf("\n");
	}
}
