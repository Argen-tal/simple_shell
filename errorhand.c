#include "shell.h"

/**
 * custom_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void custom_eputs(char *str)
{
	int i;

    if (!str)
        return;

    for (i = 0; str[i] != '\0'; i++)
    {
        custom_eputchar(str[i]);
    }
}

/**
 * custom_eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_eputchar(char c)
{
    static int i;
    static char buf[CUSTOM_WRITE_BUF_SIZE];

    if (c == CUSTOM_BUF_FLUSH || i >= CUSTOM_WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != CUSTOM_BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * custom_putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putfd(char c, int fd)
{
    static int i;
    static char buf[CUSTOM_WRITE_BUF_SIZE];

    if (c == CUSTOM_BUF_FLUSH || i >= CUSTOM_WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != CUSTOM_BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * custom_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int custom_putsfd(char *str, int fd)
{
    int i = 0;
    int j;

    if (!str)
        return (0);
    for (j = 0; str[j] != '\0'; j++)
    {
        i += custom_putfd(str[j], fd);
    }
    return (i);
}

