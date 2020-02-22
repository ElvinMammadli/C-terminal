#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_SIZE 256
#define BLUE  "\x1B[0;34m" // write blue 
#define RESET "\x1B[0m" 


void run (char ** commands); // execute command
char **partition(char *input); // for divide input to part for execvp()



int main(int argc, char const *argv[]) {
    char command[256]; //command array 
    char **commands; // commands array , array of strings
    int status=1;
    char pcname[]="Alvin-PC";  
    system("clear");
    printf("Write EXIT for exit\n");

    while (status) {  
        printf(BLUE "%s%s ",pcname,RESET); // write pc name 
        scanf(" %[^\n]s",command); //scanf command from user 
        commands =partition(command);
  		  run(commands);
  		  free(commands);

        if(!strcmp(command,"exit")){ 
            status=0;
            system("clear");

        }
    }
    return 0;
}



char **partition(char *command){

   int j,i = 0,k=0;
	 char **command_array;
	 char *tmp;
   int n = strlen(command);
   command_array = (char *)malloc(16*sizeof(char *));

	 while(i<n){
		   j=0;
		   tmp = (char *)malloc(60*sizeof(char *)) ;//assign to tmp partition of inputs
		      while((command[i]!=' ')&&(i<n)){
			         tmp[j]=command[i];
			          j++;
			          i++;
		      }
		   i++;
		   tmp[j]='\0';
		   command_array[k] = tmp;
		   k++;
	 }

	command_array[k] = NULL;

	return command_array;
}

void run(char ** commands){
  int retn ;
  pid_t p_id;
  p_id = fork(); //create process
  if (p_id == 0){//run execvp
		 if (execvp(commands[0],commands)){
       printf("\n %s:  command not found\n",commands[0] );
     }
  }
  else if(p_id==-1){
    printf("Can't run"); // cant create process
  }
  else{
    waitpid(p_id, &retn, 0); //wait parent

  }
}

