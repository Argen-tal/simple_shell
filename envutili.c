#include "shell.h"

/**
 * custom_myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int custom_myenv(custom_info_t *info)
{
    custom_list_t *node = info->env;
    while (node)
    {
        custom_print_list_str(node);
        node = node->next;
    }
    return (0);
}

/**
 * custom_getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: environment variable name
 *
 * Return: the value
 */
char *custom_getenv(custom_info_t *info, const char *name)
{
    custom_list_t *node = info->env;
    char *p;

    while (node)
    {
        p = custom_starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * custom_mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int custom_mysetenv(custom_info_t *info)
{
    if (info->argc != 3)
    {
        custom_eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (custom_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * custom_myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int custom_myunsetenv(custom_info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        custom_eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        custom_unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * custom_populate_env_list - populates environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int custom_populate_env_list(custom_info_t *info)
{
    custom_list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        custom_add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}

