#include "shell.h"

/**
 * _myenv - prints the current environment
 *
 * This function prints the current environment.
 * The `info` structure is used to
 * maintain a constant function prototype.
 *
 * @info: structure containing potential arguments
 *
 * Return: This function always returns 0 to indicate success.
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 *
 * This function gets the value of an environment variable.
 * The `info` structure
 * is used to maintain a constant function prototype.
 *
 * @info: structure containing potential arguments
 * @name: name of the environment variable
 *
 * Return: On success, this function returns the value of the environment
 * variable. If the environment variable does not exist, NULL is returned.
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - creates or modifies an environment variable
 *
 * This function creates or modifies an environment variable. The `info`
 * structure is used to maintain a constant function prototype.
 *
 * @info: structure containing potential arguments
 * @name: name of the environment variable
 * @value: value to be assigned to the environment variable
 *
 * Return: This function always returns 0 to indicate success.
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - removes an environment variable
 *
 * This function removes an environment variable. The `info` structure is used
 * to maintain a constant function prototype.
 *
 * @info: structure containing potential arguments
 * @name: name of the environment variable
 *
 * Return: This function always returns 0 to indicate success.
 */

int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates the environment linked list
 *
 * This function populates the environment linked list with the current
 * environment variables. The `info` structure is used to maintain a constant
 * function prototype.
 *
 * @info: structure containing potential arguments
 *
 * Return: This function always returns 0 to indicate success.
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
