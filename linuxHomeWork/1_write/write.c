/*建立一个结构体数组in，输入10名学生的姓名，班级，三门课程的成绩。
  将这写信息写入文件info.txt中，随后将文件中的信息读入数组out
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
	fp = fopen("info.txt","wt");
	for(i = 0; i < N; i++)
	{
		printf("Please input student_%d infomation:\n",i+1);
		printf("Name Class grade_a grade_b grade_c\n");
		scanf("%s %s %d %d %d",xinxi[i].name,xinxi[i].class,&xinxi[i].grade_a,&xinxi[i].grade_b,&xinxi[i].grade_c);
		fprintf(fp,"%s %s %d %d %d",xinxi[i].name,xinxi[i].class,xinxi[i].grade_a,xinxi[i].grade_b,xinxi[i].grade_c);
		fputc('\n',fp);
	}
	fclose(fp);
}
