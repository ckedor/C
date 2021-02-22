// PROCESSOS
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
   pid_t pid[3];
   int status;
   char x;
   int i;

   x = 'a';
   pid[0] = fork();
   if ((int)pid[0] == 0){
      for(i = 0; i < 100000; i++){
         printf("%c",x);
         fflush(stdout);
      }
      exit(0);
   }
   
   x = 'b';
   pid[1] = fork();
   if ((int)pid[1] == 0) {
      for(i = 0; i < 100000; i++){
         printf("%c",x);
         fflush(stdout);
      }
      exit(0); 
   }

   x = 'c';
   pid[2] = fork();
   if ((int)pid[2] == 0) {
      for(i = 0; i < 100000; i++){
         printf("%c",x);
         fflush(stdout);
      }
      exit(0);
   }

   for (i=0;i<3;i++)
      waitpid(pid[i],&status,0);
   printf("\nFIM\n");
 }
