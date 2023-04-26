#include "main.h"

/**
 * prompt - Function that displays a command promtp to the user
 * @av: Command line arguments
 * @envp: Environmental variable
 * Return: void
 */

void prompt(char **av, char **envp)
{
	char *lineptr = NULL, *argv[] = {NULL, NULL};
	size_t n = 0;
	int i, wstatus;
	ssize_t stream;
	pid_t pid;

	while (1)
	{
		printf("cisfun$ ");

		stream = getline(&lineptr, &n, stdin);
		if (stream == -1)
		{
			free(lineptr);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (lineptr[i])
		{
			if (lineptr[i] == '\n')
				lineptr[i] = 0;
			i++;
		}
		argv[0] = lineptr;
		pid = fork();
		if (pid == -1)
		{
			free(lineptr);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(argv[0], argv, envp) == -1)
				printf("%s: No such file or directory\n", av[0]);
		}
		else
		{
			wait(&wstatus);
		}
	}
}
