#include "shell.h"

/**
 * main - Entry point of the simple shell program
 * @argc: The number of arguments
 * @argv: The array of arguments
 * @env: The array of environment variables
 * Return: 0 on success, or the exit status of the last command executed
 */
/**
 * find_path - Find the path to a command.
 * @cmd: The command name.
 * @env: The array of environment variables.
 * Return: The path to the command, or NULL if the command cannot be found.
 */

char *find_path(char *cmd, char **env)
{
    char *path, *dir;
    int i;

    for (i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], "PATH=", 5) == 0) {
            path = env[i];
            break;
        }
    }

    if (path == NULL) {
        return NULL;
    }

    while ((dir = strtok(path, ":")) != NULL) {
        char *full_path = malloc(sizeof(char) * (_strlen(dir) + _strlen(cmd) + 2));
        if (full_path == NULL) {
            return NULL;
        }

        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, cmd);

        if (access(full_path, X_OK) == 0) {
            return full_path;
        }

        free(full_path);
    }

    return NULL;
}
int main(int argc, char **argv, char **env)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *token;
    char **args;
    int i, status;

    (void)argc;
    (void)argv;

    signal(SIGINT, sigint_handler);

    while (1) {
        if (isatty(STDIN_FILENO)) {
            write(STDOUT_FILENO, "$ ", 2);
        }

        nread = getline(&line, &len, stdin);
        if (nread == -1) {
            if (isatty(STDIN_FILENO)) {
                write(STDOUT_FILENO, "\n", 1);
            }
            free(line);
            exit(0);
        }

        line[nread - 1] = '\0';

        args = malloc(sizeof(char *) * 32);
        if (args == NULL) {
            free(line);
            exit(1);
        }

        token = strtok(line, " \t\n\r");
        i = 0;
        while (token != NULL) {
            args[i] = token;
            i++;
            token = strtok(NULL, " \t\n\r");
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            free(line);
            free(args);
            exit(0);
        }

        if (strcmp(args[0], "env") == 0) {
            print_env(env);
            free(line);
            free(args);
            continue;
        }

        status = execute(args, env);
        if (status == -1) {
            perror("Error");
        }

        free(args);
    }

    free(line);
return (status);
}
