#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Structure for linked list of paths */
typedef struct list_path {
    char *dir;
    struct list_path *p;
} list_path;

/* Environment variable */
extern char **environ;

/* Function declarations */
char *_strdup(const char *str);
char *concat_all(const char *name, const char *sep, const char *value);
int _strlen(const char *s);
int _putchar(char c);
void _puts(const char *str);

char **splitstring(char *str, const char *delim);
void execute(char **argv);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void freearv(char **arv);

void exitt(char **arv);
int _atoi(char *s);
void env(char **arv);
void _setenv(char **arv);
void _unsetenv(char **arv);
char **copy_environ(char **env);
void free_2d_array(char **arr);

void(*checkbuild(char **arv))(char **arv);
char *_getenv(const char *name);
list_path *add_node_end(list_path **head, char *str);
list_path *linkpath(char *path);
char *_which(char *filename, list_path *head);
void free_list(list_path *head);

#endif /* SHELL_H */

