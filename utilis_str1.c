#include "shell.h"

/**
 * custom_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *custom_strcpy(char *dest, char *src)
{
    if (dest == src || src == NULL)
        return dest;

    for (int i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

/**
 * custom_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *custom_strdup(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return NULL;

    while (*str++)
    {
        length++;
    }

    ret = malloc(sizeof(char) * (length + 1));

    if (!ret)
        return NULL;

    for (int i = 0; i < length; i++)
    {
        ret[i] = str[-i - 1];
    }

    ret[length] = '\0';
    return ret;
}

/**
 * custom_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void custom_puts(char *str)
{
    if (str == NULL)
        return;

    for (int i = 0; str[i] != '\0'; i++)
    {
        custom_putchar(str[i]);
    }
}

/**
 * custom_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char c)
{
    static int i;
    static char buf[CUSTOM_WRITE_BUF_SIZE];

    if (c == CUSTOM_BUF_FLUSH || i >= CUSTOM_WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (c != CUSTOM_BUF_FLUSH)
    {
        buf[i++] = c;
    }
    return 1;
}

