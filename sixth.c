#include "shell.h"

void exitt(char **arv) {
    if (arv[1]) {
        int n = _atoi(arv[1]);
        if (n <= -1)
            n = 2;
        freearv(arv);
        exit(n);
    }

    freearv(arv);
    exit(0);
}

int _atoi(char *s) {
    int i, integer, sign = 1;

	i = 0;
	integer = 0;
	while (!((s[i] >= '0') && (s[i] <= '9')) && (s[i] != '\0'))
	{
		if (s[i] == '-')
		{
			sign = sign * (-1);
		}
		i++;
	}
	while ((s[i] >= '0') && (s[i] <= '9'))
	{
		integer = (integer * 10) + (sign * (s[i] - '0'));
		i++;
	}
	return (integer);
}

void env(char **arv __attribute__ ((unused))) {
    for (int i = 0; environ[i]; i++) {
        _puts(environ[i]);
        _puts("\n");
    }
}

void _setenv(char **arv) {
    if (!arv[1] || !arv[2]) {
        perror(_getenv("_"));
        return;
    }

    char **env_copy = copy_environ(environ);

    if (!env_copy) {
        perror(_getenv("_"));
        return;
    }

    int i;
    for (i = 0; env_copy[i]; i++) {
        char *key = strtok(env_copy[i], "=");
        if (strcmp(key, arv[1]) == 0) {
            free(environ[i]);
            environ[i] = concat_all(arv[1], "=", arv[2]);
            free_2d_array(env_copy);
            return;
        }
    }

    environ[i] = concat_all(arv[1], "=", arv[2]);
    environ[i + 1] = NULL;

    free_2d_array(env_copy);
}

void _unsetenv(char **arv) {
    if (!arv[1]) {
        perror(_getenv("_"));
        return;
    }

    char **env_copy = copy_environ(environ);

    if (!env_copy) {
        perror(_getenv("_"));
        return;
    }

    int i;
    for (i = 0; env_copy[i]; i++) {
        char *key = strtok(env_copy[i], "=");
        if (strcmp(key, arv[1]) == 0) {
            free(environ[i]);
            while (environ[i + 1]) {
                environ[i] = environ[i + 1];
                i++;
            }
            environ[i] = NULL;
            free_2d_array(env_copy);
            return;
        }
    }

    free_2d_array(env_copy);
}

char **copy_environ(char **env) {
    int count = 0;
    while (env[count]) {
        count++;
    }

    char **copy = malloc(sizeof(char *) * (count + 1));
    if (!copy) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        copy[i] = _strdup(env[i]);
        if (!copy[i]) {
            free_2d_array(copy);
            return NULL;
        }
    }

    copy[count] = NULL;
    return copy;
}

void free_2d_array(char **arr) {
    if (!arr)
        return;

    for (int i = 0; arr[i]; i++) {
        free(arr[i]);
    }
    free(arr);
}

