#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#define MAX_INPUT 1024


int main(){

    char input[MAX_INPUT];
    
    while(1){
        printf("mysh> ");
        fflush(stdout);

        if(fgets(input,MAX_INPUT,stdin)==NULL){
            printf("\n");
            break;
        }

        input[strcspn(input,"\n")]=0;

        if(strlen(input)==0) continue;

        pid_t pid = fork();
        if(pid < 0){
            perror("Fork failed");
            continue;
        }

        if(pid == 0){
            char *args[] = {input,NULL};
            execvp(args[0],args);

            perror("Execution failed");
            exit(1);
        }
        else{
            wait(NULL);
        }

    }
    return 0;
}