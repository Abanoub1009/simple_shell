#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	char *command;
	ssize_t nread;
	size_t bufsize = 0;
	int status;

	while (1)
	{
		printf("#cisfun$ ");

		/* Read the command from the user */
		nread = getline(&command, &bufsize, stdin);
		if (nread == -1)
		{
			/* Handle end-of-file (Ctrl+D) */
			printf("\n");
			break;
		}

		/* Remove the newline character */
		command[nread - 1] = '\0';

		/* Fork a child process */
		pid_t pid = fork();

		if (pid == -1)
		{
			/* Forking failed */
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* Child process */
			if (execlp(command, command, NULL) == -1)
			{
				/* Executable not found */
				printf("%s: command not found\n", command);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* Parent process */
			wait(&status);
		}
	}

	free(command);

	return 0;
}
