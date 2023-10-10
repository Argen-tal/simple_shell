#include "shell.h"

/**
 * main - Entry point of the simple shell program
 * @argc: The number of arguments passed to the program
 * @argv: The array of arguments passed to the program
 * @env: The array of environment variables
 * Return: 0 on success, or the exit status of the last command executed
 */
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
    signal(SIGINT, sigint_handler); /* Handle Ctrl+C */
    while (1)
    {
        if (isatty(STDIN_FILENO)) /* Check if in interactive mode */
            write(STDOUT_FILENO, "$ ", 2); /* Print prompt */
        nread = getline(&line, &len, stdin); /* Read a line of input */
        if (nread == -1) /* Check for errors or end-of-file */
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            free(line);
            exit(0);
        }
        line[nread - 1] = '\0'; /* Remove the new line character */
        args = malloc(sizeof(char *) * 32); /* Allocate memory for the array of arguments */
        if (args == NULL) /* Check for errors in malloc */
        {
            free(line);
            exit(1);
        }
        token = strtok(line, " \t\n\r"); /* Split the line into tokens */
        i = 0;
        while (token != NULL) /* Loop through all the tokens */
        {
            args[i] = token; /* Store each token as an argument */
            i++;
            token = strtok(NULL, " \t\n\r"); /* Get the next token */
        }
        args[i] = NULL; /* Store NULL as the last element of the array */
        if (_strcmp(args[0], "exit") == 0) /* Check if the first argument is equal to "exit" */
        {
            free(line); /* Free the input line */
            free(args); /* Free the array of arguments */
            exit(0); /* Exit the shell with status code 0 */
        }
        if (_strcmp(args[0], "env") == 0) /* Check if the first argument is equal to "env" */
        {
            print_env(env); /* Print the current environment */
            free(line); /* Free the input line */
            free(args); /* Free the array of arguments */
            continue; /* Skip executing the command and continue reading another line of input */
        }
        status = execute(args, env); /* Execute the command with the arguments and environment variables */
        if (status == -1) /* Check if the command execution failed */
            perror("Error"); /* Print an error message */
        free(args); /* Free the array of arguments */
    }
    free(line);
    return (status);
}

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

    if (args[0][0] == '/' || args[0][0] == '.') /* Check if the first argument is a relative or absolute path */
        path = args[0]; /* Use it as the path to the executable file */
    else
        path = find_path(args[0], env); /* Find the path to the executable file using PATH environment variable */
    if (path == NULL) /* Check if the path was not found */
        return (-1); /* Return -1 and do not fork if the command doesn't exist */
    pid = fork(); /* Create a child process */
    if (pid == -1) /* Check for errors in fork */
        return (-1);
    if (pid == 0) /* In child process */
    {
        if (execve(path, args, env) == -1) /* Execute the command */
            exit(127); /* Exit with error code 127 if execve fails */
    }
    else /* In parent process */
    {
        wait(&status); /* Wait for the child process to terminate */
        return (WEXITSTATUS(status)); /* Return the exit status of the child process */
    }
}

/**
 * find_path - Find the path to an executable file using PATH environment variable
 * @cmd: The name of the executable file
 * @env: The array of environment variables
 * Return: The full path to the executable file, or NULL if not found
 */
char *find_path(char *cmd, char **env)
{
    char *path;
    char *token;
    char *buffer;
    int i;

    path = _getenv("PATH", env); /* Get the value of PATH environment variable */
    if (path == NULL) /* Check if PATH is not set */
        return (NULL);
    token = strtok(path, ":"); /* Split the path into tokens separated by : */
    while (token != NULL) /* Loop through all the tokens */
    {
        buffer = malloc(sizeof(char) * (_strlen(token) + _strlen(cmd) + 2)); /* Allocate memory for the buffer */
        if (buffer == NULL) /* Check for errors in malloc */
            return (NULL);
        _strcpy(buffer, token); /* Copy the token to the buffer */
        _strcat(buffer, "/"); /* Concatenate a / to the buffer */
        _strcat(buffer, cmd); /* Concatenate the command name to the buffer */
        if (access(buffer, X_OK) == 0) /* Check if the buffer is an executable file */
            return (buffer); /* Return the buffer as the path to the executable file */
        free(buffer); /* Free the buffer */
        token = strtok(NULL, ":"); /* Get the next token */
    }
    return (NULL); /* Return NULL if no path was found */
}
