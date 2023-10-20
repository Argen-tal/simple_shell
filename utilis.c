#include "shell.h"

/**
 * custom_myexit - exits the shell
 * @info: Structure containing potential arguments.
 * Return: exits with a given exit status (0) if info->argv[0] != "exit"
 */
int custom_myexit(custom_info_t *info)
{
    int exitcheck;
    int i;
    
    i = 1;
    while (info->argv[i]) {  /* Check for exit argument */
        exitcheck = custom_erratoi(info->argv[i]);
        if (exitcheck == -1)
        {
            info->status = 2;
            custom_print_error(info, "Illegal number: ");
            custom_eputs(info->argv[i]);
            custom_eputchar('\n');
            return (1);
        }
        info->err_num = custom_erratoi(info->argv[i]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * custom_mycd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int custom_mycd(custom_info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;
    int i;
    
    s = getcwd(buffer, 1024);
    if (!s)
        custom_puts("TODO: >>getcwd failure emsg here<<\n");
    
    i = 1;
    while (info->argv[i])
    {
        if (!info->argv[i])
        {
            dir = custom_getenv(info, "HOME=");
            if (!dir)
                chdir_ret = -1;
            chdir((dir = custom_getenv(info, "PWD=")) ? dir : "/");
        }
        else if (custom_strcmp(info->argv[i], "-") == 0)
        {
            if (!custom_getenv(info, "OLDPWD="))
            {
                custom_puts(s);
                custom_putchar('\n');
                return (1);
            }
            custom_puts(custom_getenv(info, "OLDPWD="));
            custom_putchar('\n');
            chdir_ret = -1;
            chdir((dir = custom_getenv(info, "OLDPWD=")) ? dir : "/");
        }
        else
            chdir_ret = chdir(info->argv[i]);
        
        if (chdir_ret == -1)
        {
            custom_print_error(info, "can't cd to ");
            custom_eputs(info->argv[i]);
            custom_eputchar('\n');
        }
        else
        {
            custom_setenv(info, "OLDPWD", custom_getenv(info, "PWD="));
            custom_setenv(info, "PWD", getcwd(buffer, 1024));
        }
        
        i++;
    }
    
    return (0);
}

/**
 * custom_myhelp - displays help information
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int custom_myhelp(custom_info_t *info)
{
    char **arg_array;
    int i;

    arg_array = info->argv;
    custom_puts("help call works. Function not yet implemented \n");

    i = 0;
    while (arg_array[i])
    {
        custom_puts(arg_array[i]);
        i++;
    }

    return (0);
}

