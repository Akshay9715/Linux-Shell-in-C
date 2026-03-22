#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

int main(){

    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    
    while(1){
        printf("mysh> ");
        fflush(stdout);

        if(fgets(input,MAX_INPUT,stdin)==NULL){
            printf("\n");
            break;
        }

        input[strcspn(input,"\n")]=0;

        if(strlen(input)==0) continue;

        int i = 0;
        char *token = strtok(input," ");

        while(token != NULL && i<MAX_ARGS-1){
            args[i++] = token;
            token = strtok(NULL," ");
        }
        args[i] = NULL;

        if(strcmp(args[0],"exit")==0){
            printf("Exiting shell...\n");
            break;
        }

        if(strcmp(args[0],"cd")==0){
            if(args[1]==NULL){
                fprintf(stderr,"cd : missing argument\n");
            }
            else if(strcmp(args[1],"~")==0){
                chdir(getenv("HOME"));
            }
            else{
                if(chdir(args[1]) != 0){
                    perror("cd failed");
                }
            }
            continue;
        }

        if(strcmp(args[0],"pwd")==0){
            char cwd[1024];
            if(getcwd(cwd,sizeof(cwd))!=NULL){
                printf("%s \n",cwd);
            }
            else{
                perror("pwd failed");
            }
            continue;
        }

        pid_t pid = fork();
        if(pid < 0){
            perror("Fork failed");
            continue;
        }

        if(pid == 0){
            
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