#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    custom_info_t info[] = { CUSTOM_INFO_INIT };
    int fd = 2;
    int i;

    for (i = 0; i < ac; i++)
    {
        fd = open(av[i], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                return 126;
            if (errno == ENOENT)
            {
                custom_puts(av[0]);
                custom_puts(": 0: Can't open ");
                custom_puts(av[i]);
                custom_putchar('\n');
                custom_putchar(CUSTOM_BUF_FLUSH);
                return 127;
            }
            return EXIT_FAILURE;
        }
        info->readfd = fd;
    }

    custom_populate_env_list(info);
    custom_read_history(info);
    custom_hsh(info, av);
    return EXIT_SUCCESS;
}

