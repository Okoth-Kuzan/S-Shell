#include "shell.h"

typedef struct {
    const char *name;
    void (*func)(char **arv);
} mybuild;

void (*checkbuild(char **arv))(char **arv) {
    mybuild T[] = {
        {"exit", exitt},
        {"env", env},
        {"setenv", _setenv},
        {"unsetenv", _unsetenv},
        {NULL, NULL}
    };

    for (int i = 0; T[i].name != NULL; i++) {
        int j = 0;
        while (T[i].name[j] == arv[0][j]) {
            if (T[i].name[j] == '\0') {
                return T[i].func;
            }
            j++;
        }
    }
    return (NULL);
}

