#include "shell.h"

/**
 * execute_command - Forks a child process and executes the command
 * @cmd: The executable path/command to run
 * @prog_name: Name of the shell program for error reporting
 *
 * Return: void
 */
void execute_command(char *cmd, char *prog_name)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = cmd;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd, args, environ) == -1)
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
 * main - Entry point for the simple shell interpreter
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

		if (line[read_bytes - 1] == '\n')
			line[read_bytes - 1] = '\0';

		if (line[0] != '\0')
			execute_command(line, av[0]);
	}

	free(line);
	return (0);
}
