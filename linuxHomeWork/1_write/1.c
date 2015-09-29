#include <stdio.h>
int main()
{
int a[5][6], *p, i, j;
for (i = 0; i < 5; i++){
for (j = 0; j < 6; j++){
scanf("%d", a[i] + j);
}
}
p = a;
for (i = 0; i < 5 * 6; i++){
printf("%d ", *p+i);
}
return(0);
}
