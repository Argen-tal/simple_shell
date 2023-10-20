#include "shell.h"

/**
 * custom_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */
char *custom_strncpy(char *dest, char *src, int n)
{
    char *s = dest;
    int i;
    int j;

    for (i = 0; src[i] != '\0' && i < n - 1; i++)
    {
        dest[i] = src[i];
    }

    if (n > 0)
    {
        for (j = n - 1; j < n; j++)
        {
            dest[j] = '\0';
        }
    }
    return s;
}

/**
 * custom_strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *custom_strncat(char *dest, char *src, int n)
{
    char *s = dest;
    int i = 0;
    int j;

    while (dest[i] != '\0')
    {
        i++;
    }

    for (j = 0; src[j] != '\0' && j < n; j++)
    {
        dest[i] = src[j];
        i++;
    }

    if (n > 0)
    {
        dest[i] = '\0';
    }

    return s;
}

/**
 * custom_strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: a pointer to the memory area s
 */
char *custom_strchr(char *s, char c)
{
    do {
        if (*s == c)
            return s;
    } while (*s++ != '\0');

    return NULL;
}

