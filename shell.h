#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void free_vector(char **vector);
char *_strdup(const char *str);
void execute_command(char *cmd, char *prog_name);

#endif /* SHELL_H */
