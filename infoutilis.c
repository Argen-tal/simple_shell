#include "shell.h"

/**
 * custom_clear_info - initializes info_t struct
 * @info: struct address
 */
void custom_clear_info(custom_info_t *info)
{
    custom_ffree(info->arg);
    info->arg = NULL;
    custom_ffree(info->argv);
    info->argv = NULL;
    info->argc = 0;
}

/**
 * custom_set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void custom_set_info(custom_info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = custom_strtow(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = custom_strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;
        custom_replace_alias(info);
        custom_replace_vars(info);
    }
}

/**
 * custom_free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void custom_free_info(custom_info_t *info, int all)
{
    custom_ffree(info->argv);
    info->argv = NULL;
    custom_ffree(info->path);
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buf)
            custom_ffree(info->arg);
        if (info->env)
            custom_free_list(&(info->env));
        if (info->history)
            custom_free_list(&(info->history));
        if (info->alias)
            custom_free_list(&(info->alias));
        custom_ffree(info->environ);
        info->environ = NULL;
        custom_bfree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        custom_putchar(BUF_FLUSH);
    }
}
