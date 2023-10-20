#include "shell.h"

/**
 * custom_myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int custom_myhistory(custom_info_t *info)
{
    custom_list_t *node = info->history;
    while (node)
    {
        custom_print_list_str(node);
        node = node->next;
    }
    return (0);
}

/**
 * custom_unset_alias - unsets an alias
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int custom_unset_alias(custom_info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = custom_strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = custom_delete_node_at_index(&(info->alias),
        custom_get_node_index(info->alias, custom_node_starts_with(info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * custom_set_alias - sets an alias
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int custom_set_alias(custom_info_t *info, char *str)
{
    char *p;

    p = custom_strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (custom_unset_alias(info, str));

    custom_unset_alias(info, str);
    return (custom_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * custom_print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int custom_print_alias(custom_list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = custom_strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            custom_putchar(*a);
        custom_putchar('\'');
        custom_puts(p + 1);
        custom_puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * custom_myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int custom_myalias(custom_info_t *info)
{
    char *p = NULL;
    int i;
    custom_list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            custom_print_alias(node);
            node = node->next;
        }
        return (0);
    }
    
    for (i = 1; info->argv[i]; i++)
    {
        p = custom_strchr(info->argv[i], '=');
        if (p)
            custom_set_alias(info, info->argv[i]);
        else
            custom_print_alias(custom_node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}

