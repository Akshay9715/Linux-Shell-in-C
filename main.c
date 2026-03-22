#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>

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

        int background = 0;

        if(i>0 && strcmp(args[i-1],"&")==0){
            background = 1;
            args[i-1] = NULL;
        }

        int input_redirect = 0, output_redirect = 0;
        char *input_file = NULL;
        char *output_file = NULL;

        for(int j = 0;args[j]!=NULL;j++){
            if(strcmp(args[j],"<")==0){
                input_redirect = 1;
                input_file = args[j+1];
                args[j] = NULL;
            }
            else if(strcmp(args[j],">")==0){
                output_redirect = 1;
                output_file = args[j+1];
                args[j] = NULL;
            }
        }


        pid_t pid = fork();
        if(pid < 0){
            perror("Fork failed");
            continue;
        }

        if(pid == 0){

            if(input_redirect){
                int fd = open(input_file,O_RDONLY);
                if(fd < 0){
                    perror("Input file error");
                    exit(1);
                }
                dup2(fd,STDIN_FILENO);
                close(fd);
            }
            
            if(output_redirect){
                int fd = open(output_file,O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if(fd < 0){
                    perror("Output file error");
                    exit(1);
                }
                dup2(fd,STDOUT_FILENO);
                close(fd);
            }
            execvp(args[0],args);
            perror("Execution failed");
            exit(1);
        }
        else{
            if(!background){
                wait(NULL);
            }
            else{
                printf("[Background PID : %d]\n",pid);
            }
        }

    }
    return 0;
}