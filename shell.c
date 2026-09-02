#include "shell.h"

/**
 * execute_command - Forks and executes a command
 * @args: Null-terminated array of command arguments
 * @prog_name: Name of the shell program
 * @count: Input line number
 *
 * Return: Exit status of the command
 */
int execute_command(char **args, char *prog_name, int count)
{
	char *command_path;
	pid_t pid;
	int status;

	command_path = find_command(args[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, count, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		free(command_path);
		return (1);
	}

	if (pid == 0)
	{
		execve(command_path, args, environ);
		perror(prog_name);
		free(command_path);
		_exit(126);
	}

	waitpid(pid, &status, 0);
	free(command_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));

	return (1);
}

/**
 * tokenize_line - Splits an input line into arguments
 * @line: Input line
 * @args: Array to store command arguments
 *
 * Return: Number of arguments
 */
static int tokenize_line(char *line, char **args)
{
	char *token;
	int i = 0;

	token = strtok(line, " \t\n\r");
	while (token != NULL && i < MAX_TOKENS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n\r");
	}

	args[i] = NULL;
	return (i);
}

/**
 * handle_builtin - Handles shell built-in commands
 * @args: Command arguments
 * @line: Input buffer
 * @status: Status of the previous command
 *
 * Return: void
 */
static void handle_builtin(char **args, char *line, int status)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(status);
	}
}

/**
 * main - Entry point for simple shell interpreter
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: Status of the last command
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_bytes;
	char *args[MAX_TOKENS];
	int count = 0, status = 0;

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
			return (status);
		}

		count++;
		if (tokenize_line(line, args) > 0)
		{
			handle_builtin(args, line, status);
			status = execute_command(args, av[0], count);
		}
	}
}
