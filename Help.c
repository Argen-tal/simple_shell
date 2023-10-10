#include "shell.h"

/**
 * print_env - Print the current environment
 * @env: The array of environment variables
 */
void print_env(char **env)
{
    int i;

    for (i = 0; env[i] != NULL; i++) /* Loop through all the environment variables */
    {
        write(STDOUT_FILENO, env[i], _strlen(env[i])); /* Write each variable to standard output */
        write(STDOUT_FILENO, "\n", 1); /* Write a new line character after each variable */
    }
}
