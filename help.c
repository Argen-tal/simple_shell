#include "shell.h"

/**
* execute - Execute a command with arguments and environment variables
* @args: The array of arguments
* @env: The array of environment variables
* Return: 0 on success, or -1 on failure
*/
int execute(char **args, char **env)
{
	pid_t pid;
	int status;
	char *path;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (args[0][0] == '/' || args[0][0] == '.')
			path = args[0];
		else
			path = find_path(args[0], env);
		if (path == NULL)
		{
			free(path);
			return (NULL);
		}
		if (path[0] == '\0' || strrchr(path, ':') == path + _strlen(path))
			token = ".";
		else
			token = strtok(path, ":");
		while (token != NULL)
		{
			buffer = malloc(sizeof(char) * (_strlen(token) + _strlen(cmd) + 2));
			if (buffer == NULL)
				return (NULL);
			_strcpy(buffer, token);
			_strcat(buffer, "/");
			_strcat(buffer, cmd);
			if (access(buffer, X_OK) == 0)
				return (buffer);
			free(buffet);
			token = strtok(NULL, ":");
		}
	}
	return (NULL);
}

/**
* sigint_handler - Hanlde the SIGINT signal
* @signum: the signal number
*/
void sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
* print_env - Print the current environment
* @env: the array of environment variables
*/
void print_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		write(STDOUT_FILENO, env[i], strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
