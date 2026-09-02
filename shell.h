#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_TOKENS 1024

extern char **environ;

void free_vector(char **vector);
char *_strdup(const char *str);
char *find_command(char *command);
void execute_command(char **args, char *prog_name, int count);

#endif /* SHELL_H */
