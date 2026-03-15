//A shell uses a REPL loop
#include "shell.h"

void parse(char *input , char *args[]){
    int i =0;
    char *token = strtok(input, "\n");//Takes the first token
    while (token != NULL){
        args[i] = token;
        i++;

        token = strtok(NULL , "\n");
    }
    args[i] = NULL;
};

int main (void){
    //Reading user input
    char input[1024]; //buffer to contain the characters
    while (1){
        printf("Myshell>> " );
        fflush(stdout);//for the prompt appear immediately
        if (fgets(input , sizeof(input) , stdin) == NULL){
            printf("\n");
            break;
        }
        // TODO: parse and execute here
    }
    return 0;
}