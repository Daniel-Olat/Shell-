#include <stdio.h>


void lsh_loop(void);

int main(int argc , char **argv){
    // Load config files if any
    // Basic command loop
    lsh_loop(); // Read Parse and excecute
    return EXIT_SUCCESS;//any shutdown or cleaning
}

void lsh_loop(void){
    char *line ;
    char **args;
    int status;

    do{
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);// zero terminates the shell ,  non zero keeps the loop going

        free(line);
        free(args);
    } while (status);
}

#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void){
    int bufsize = LSH_RL_BUFSIZE ; 
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer){
        fprint(stderr  , "lsh: Allocation Error\n");
        exit(EXIT_FAILURE);
    }

    while(1);
    c = getchar();
    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
        buffer[position] = '\0';
        return buffer;
    } else {
    buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
        bufsize += LSH_RL_BUFSIZE;
        buffer = realloc(buffer, bufsize);
    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
        }
    }
}