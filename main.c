#include "main.h"

/**
 * main - Simple shell
 * @ac: Number of command line args to be passed
 * @av: command line arguments
 * @envp: Environment variable
 * Return: 0 if success
 */

int main(int ac, char **av, char **envp)
{
	if (ac == 1)
	{
		prompt(av, envp);
	}

	return (0);
}
