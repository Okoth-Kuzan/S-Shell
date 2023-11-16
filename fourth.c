#include "shell.h"

char **splitstring(char *str, const char *delim)
{
	if (!str || !delim)
		return (NULL);

	char **array = NULL;
	char *token;
	int wn = 0;

	char *copy = _strdup(str);

	if (!copy)
	{
		perror(_getenv("_"));
		return (NULL);
	}

	token = strtok(copy, delim);
	
	while (token) {
        wn++;
        array = _realloc(array, sizeof(char *) * (wn - 1), sizeof(char *) * wn);
        if (!array) {
            free(copy);
            return NULL;
        }
        array[wn - 1] = _strdup(token);
        token = strtok(NULL, delim);
    }

    free(copy);
    return array;
}

void execute(char **argv) {
    if (!argv || !argv[0])
        return;

    pid_t pid = fork();
    if (pid == -1) {
        perror(_getenv("_"));
    } else if (pid == 0) {
        if (execve(argv[0], argv, environ) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

void *my_realloc(void *ptr, size_t old_size, size_t new_size) {
    if (!ptr) {
        return malloc(new_size);
    }

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size) {
        return ptr;
    }

    void *new_ptr = malloc(new_size);
    if (!new_ptr) {
        return NULL;
    }

    size_t min_size = old_size < new_size ? old_size : new_size;
    memcpy(new_ptr, ptr, min_size);
    free(ptr);

    return new_ptr;
}

void freearv(char **arv) {
    if (!arv)
        return;

    for (int i = 0; arv[i]; i++) {
        free(arv[i]);
    }
    free(arv);
}

