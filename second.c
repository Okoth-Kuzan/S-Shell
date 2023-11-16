#include "shell.h"

void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		_puts("\n#cisfun$ ");
	}
}

void handle_EOF(int len, char *buff)
{
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buff);
		}
		exit(0);
	}
}

void print_shell_prompt(void)
{
	if (isatty(STDIN_FILENO))
		_puts("#cisfun$ ");
}

int main(void)
{
	ssize_t len = 0;
	char *buff = NULL, *value, *pathname, **arv;
	size_t size = 0;
	list_path *head = NULL;
	void (*f)(char **);

	signal(SIGINT, sig_handler);
	while (len != EOF)
	{
		print_shell_prompt();
		len = getline(&buff, &size, stdin);
		handle_EOF(len, buff);

		arv = splitstring(buff, " \n");
		if (!arv || !arv[0])
			execute(arv);
		else
		{
			value = _getenv("PATH");
			head = linkpath(value);
			pathname = _which(arv[0], head);
			f = checkbuild(arv);

			if (f)
			{
				free(buff);
				f(arv);
			}
			else if (!pathname)
				execute(arv);
			else if (pathname)
			{
				free(arv[0]);
				arv[0] = pathname;
				execute(arv);
			}
		}
	}
	free_list(head);
	freearv(arv);
	free(buff);
	return (0);
}

