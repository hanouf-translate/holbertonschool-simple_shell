#include "shell.h"

/**
 * execute_command - Forks a child process and executes a command with args
 * @args: Null-terminated array of command strings
 * @prog_name: Name of the shell program for error reporting
 *
 * Return: void
 */
void execute_command(char **args, char *prog_name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return;
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(prog_name);
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - Entry point for simple shell interpreter
 * @ac: Argument count (unused)
 * @av: Argument vector
 *
 * Return: Always 0 on success
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_bytes;
	char *args[MAX_TOKENS];
	char *token;
	int i;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		read_bytes = getline(&line, &len, stdin);
		if (read_bytes == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		i = 0;
		token = strtok(line, " \t\n\r");
		while (token != NULL && i < MAX_TOKENS - 1)
		{
			args[i++] = token;
			token = strtok(NULL, " \t\n\r");
		}
		args[i] = NULL;

		if (args[0] != NULL)
			execute_command(args, av[0]);
	}

	free(line);
	return (0);
}
