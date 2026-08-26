#include "shell.h"

/**
 * free_vector - Frees a NULL-terminated array of strings
 * @vector: Double pointer to the array of strings
 */
void free_vector(char **vector)
{
	int i = 0;

	if (vector == NULL)
		return;

	while (vector[i] != NULL)
	{
		free(vector[i]);
		i++;
	}
	free(vector);
}

/**
 * _strdup - Duplicates a string using dynamic memory allocation
 * @str: String to duplicate
 *
 * Return: Pointer to the duplicated string, or NULL on failure
 */
char *_strdup(const char *str)
{
	char *dup;
	size_t len = 0, i;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		dup[i] = str[i];

	return (dup);
}
