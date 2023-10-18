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
        char *token;

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
                        return (-1);

                token = strtok(path, ":");
                while (token != NULL)
                {
                        char *buffer = malloc(sizeof(char) * (_strlen(token) + _strlen(args[0]) + 2));
                        if (buffer == NULL)
                        {
                                free(path);
                                return (-1);
                        }

                        strcpy(buffer, token);
                        strcat(buffer, "/");
                        strcat(buffer, args[0]);

                        if (access(buffer, X_OK) == 0)
                        {
                                execve(buffer, args, env);
                                perror("execve");
                                free(buffer);
                                free(path);
                                exit(1);
                        }

                        free(buffer);
                        token = strtok(NULL, ":");
                }

                free(path);
                exit(1);
        }

        waitpid(pid, &status, 0);
        return (status);
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
                if (env[i] != NULL) {
                        write(STDOUT_FILENO, env[i], strlen(env[i]));
 
                       write(STDOUT_FILENO, "\n", 1);
                }
        }
}

