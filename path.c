#include "shell.h"

/**
 * get_env_value - Gets the value of an environment variable
 * @name: Name of the environment variable
 *
 * Return: Pointer to the value, or NULL if not found
 */
static char *get_env_value(char *name)
{
	int i;
	size_t len;

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

/**
 * make_command_path - Builds a full command path
 * @dir: Directory from PATH
 * @dir_len: Length of the directory string
 * @command: Command name
 *
 * Return: Allocated full path, or NULL on failure
 */
static char *make_command_path(char *dir, size_t dir_len, char *command)
{
	char *full;
	size_t cmd_len;

	if (dir_len == 0)
		return (_strdup(command));

	cmd_len = strlen(command);
	full = malloc(dir_len + cmd_len + 2);
	if (full == NULL)
		return (NULL);

	memcpy(full, dir, dir_len);
	full[dir_len] = '/';
	memcpy(full + dir_len + 1, command, cmd_len + 1);
	return (full);
}

/**
 * find_command - Finds an executable command using PATH
 * @command: Command entered by the user
 *
 * Return: Allocated executable path, or NULL if not found
 */
char *find_command(char *command)
{
	char *path, *start, *end, *full;
	size_t dir_len;

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (_strdup(command));
		return (NULL);
	}

	path = get_env_value("PATH");
	if (path == NULL)
		return (NULL);

	start = path;
	while (1)
	{
		end = strchr(start, ':');
		dir_len = end ? (size_t)(end - start) : strlen(start);

		full = make_command_path(start, dir_len, command);
		if (full == NULL)
			return (NULL);

		if (access(full, X_OK) == 0)
			return (full);

		free(full);

		if (end == NULL)
			break;

		start = end + 1;
	}

	return (NULL);
}
