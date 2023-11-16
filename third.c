#include "shell.h"

char *_getenv(const char *name)
{
	if (!name)
		return (NULL);

	for (int i = 0; environ[i]; i++)
	{
		if (strncmp(name, environ[i], strlen(name)) == 0 && environ[i][strlen(name)] == '=')
		{
			return environ[i] + strlen(name) + 1;
		}
	}
	return (NULL);
}

list_path *add_node_end(list_path **head, char *str)
{
	if (!head || !str)
		return NULL;

	list_path *new = malloc(sizeof(list_path));
	if (!new)
		return (NULL);

	new->dir = str;
	new->p = NULL;

	if (!*head)
	{
		*head = new;
	}
	else
	{
		list_path *tmp = *head;
		while (tmp->p)
			tmp = tmp->p;
		tmp->p = new;
	}
	return (*head);
}

list_path *linkpath(char *path)
{
	list_path *head = NULL;
	char *token;
	char *cpath = _strdup(path);

	token = strtok(cpath, ":");
	while (token)
	{
		head = add_node_end(&head, token);
		token = strtok(NULL, ":");
	}
	return (head);
}

char *_which(char *filename, list_path *head)
{
	struct stat st;
	char *string;

	list_path *tmp = head;

	while (tmp)
	{
		string = concat_all(tmp->dir, "/", filename);
		if (stat(string, &st) == 0)
		{
			return (string);
		}
		free(string);
		tmp = tmp->p;
	}
	return (NULL);
}

void free_list(list_path *head)
{
	while (head)
	{
		list_path *storage = head->p;
		free(head->dir);
		free(head);
		head = storage;
	}
}

