#include "main.h"

/**
 * prompt - Function that promts for user input
 * Return: void
 */

void prompt(void)
{
	char *lineptr, **args;
	pid_t pid;
	int wstatus;

	do {
		printf("cisfun$ ");
		lineptr = read_line();
		args = parse_line(lineptr);
		pid = fork();

		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("Error");
			}
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("Error");
		}
		else
		{
			waitpid(pid, &wstatus, WUNTRACED);
		}

		free(lineptr);
		free(args);

	} while (wstatus != -1);
}

/**
 * read_line - Function that reads line of inputs
 * Return: input line
 */

char *read_line(void)
{
	char *lineptr = NULL;
	size_t n = 0;

	getline(&lineptr, &n, stdin);

	return (lineptr);
}

/**
 * parse_line - Function that parses a line of input
 * @lineptr: Line entered by user
 * Return: Line token
 */

char **parse_line(char *lineptr)
{
	int n = 64, i = 0;
	char *token, **tokens = malloc(n * sizeof(char *));

	if (!tokens)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(lineptr, " \n");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		if (i >= n)
		{
			n += 64;
			tokens = realloc(tokens, n * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \n");
	}

	tokens[i] = NULL;

	return (tokens);
}
