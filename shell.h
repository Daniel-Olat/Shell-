#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Platform-specific headers */
#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <process.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

/* Function prototypes */
void parse(char *input, char *args[]);
void excecute_command(char *args[]);

#endif