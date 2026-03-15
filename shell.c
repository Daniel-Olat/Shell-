// A shell uses a REPL loop
#include "shell.h"

// Parses the input into tokens separated by whitespace
void parse(char *input , char *args[]){
    int i = 0;
    char *token = strtok(input, "  \t\r\n");
    while (token != NULL){
        args[i++] = token;
        token = strtok(NULL, "  \t\r\n");
    }
    args[i] = NULL;
}

int main (void){
    char input[1024];
    char *args[24];

    while (1){
        printf("Myshell>> ");
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL){
            printf("\n");
            break;
        }
        parse(input, args);
        if (args[0] == NULL) continue;
        excecute_command(args);
    }
    return 0;
}

void excecute_command(char *args[]){
#if defined(_WIN32) || defined(_WIN64)
    /* Use cmd.exe /C on Windows so shell built-ins work (dir, date, etc.) */
    const char *cmd = "cmd";
    /* Build argv: {"cmd", "/C", orig0, orig1, ..., NULL} */
    const char *cmd_args[32];
    int ci = 0;
    cmd_args[ci++] = "cmd";
    cmd_args[ci++] = "/C";
    for (int j = 0; args[j] != NULL && ci < (int)(sizeof(cmd_args)/sizeof(cmd_args[0]) - 1); ++j) {
        cmd_args[ci++] = args[j];
    }
    cmd_args[ci] = NULL;
    int status = _spawnvp(_P_WAIT, cmd, (const char *const *)cmd_args);
    if (status == -1){
        perror("Command failed");
    }
#else
    pid_t pid = fork();
    if (pid < 0){
        perror("fork failed");
        return;
    }
    if (pid == 0){
        execvp(args[0], args);
        perror("Command failed");
        exit(1);
    } else {
        wait(NULL);
    }
#endif
}