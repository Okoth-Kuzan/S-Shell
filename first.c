#include "shell.h"

char *_strdup(const char *str)
{
	if (!str)
	{
		return (NULL);
	}

	size_t len = strlen(str);
	char *new_str = malloc((len + 1) * sizeof(char));

	if (!new_str)
	{
		return (NULL);
	}

	strcpy(new_str, str);
	return (new_str);
}

char *concat_all(const char *name, const char *sep, const char *value)
{
	if (!name || !sep || !value)
	{
		return (NULL);
	}

	size_t len_name = strlen(name);
	size_t len_sep = strlen(sep);
	size_t len_value = strlen(value);

	char *result = malloc((len_name + len_sep + len_value + 1) * sizeof(char));

	if (!result)
	{
		return (NULL);
	}
	strcpy(result, name);
	strcat(result, sep);
	strcat(result, value);
	return (result);
}

size_t _strlen(const char *s)
{
	size_t len = 0;

	while (*s++)
	{
		len++;
	}
	return (len);
}

int _putchar(char c)
{
	return (putchar(c));
}

void _puts(const char *str)
{
	while (*str)
	{
		_putchar(*str++);
	}
}

