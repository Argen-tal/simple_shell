#include "shell.h"

/**
 * custom_is_chain - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int custom_is_chain(custom_info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CUSTOM_CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CUSTOM_CMD_AND;
    }
    else if (buf[j] == ';') /* found the end of this command */
    {
        buf[j] = 0; /* replace semicolon with null */
        info->cmd_buf_type = CUSTOM_CMD_CHAIN;
    }
    else
    {
        return 0;
    }
    *p = j;
    return 1;
}

/**
 * custom_check_chain - checks if we should continue chaining based on the last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void custom_check_chain(custom_info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmd_buf_type == CUSTOM_CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (info->cmd_buf_type == CUSTOM_CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * custom_replace_alias - replaces aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int custom_replace_alias(custom_info_t *info)
{
    int i;
    custom_list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = custom_node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return 0;
        custom_free_info(info, 0);
        p = custom_strchr(node->str, '=');
        if (!p)
            return 0;
        p = custom_strdup(p + 1);
        if (!p)
            return 0;
        info->argv[0] = p;
    }
    return 1;
}

/**
 * custom_replace_vars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int custom_replace_vars(custom_info_t *info)
{
    int i = 0;
    custom_list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (custom_strcmp(info->argv[i], "$?") == 0)
        {
            custom_replace_string(&(info->argv[i]), custom_strdup(custom_convert_number(info->status, 10, 0)));
            continue;
        }
        if (custom_strcmp(info->argv[i], "$$") == 0)
        {
            custom_replace_string(&(info->argv[i]), custom_strdup(custom_convert_number(getpid(), 10, 0)));
            continue;
        }
        node = custom_node_starts_with(info->env, &info->argv[i][1], '=');
        if (node)
        {
            custom_replace_string(&(info->argv[i]), custom_strdup(custom_strchr(node->str, '=') + 1));
            continue;
        }
        custom_replace_string(&info->argv[i], custom_strdup(""));
    }
    return 0;
}

/**
 * custom_replace_string - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

