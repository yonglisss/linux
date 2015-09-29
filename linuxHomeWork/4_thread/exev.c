#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv[] )
{
  // int i;
//   pid_t pid1,pid2,pid3;
 //  int stat_val;
//   char *envp[] = {"PATH = .",NULL};    

   if (argc < 2)
   {
	   printf("argc error\n");
	   exit(-1);
   }
   execvp(argv[1],&argv[1]);
//   return 0;
}
