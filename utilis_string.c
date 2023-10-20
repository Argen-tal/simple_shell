#include "shell.h"

/**
 * custom_strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int custom_strlen(char *s)
{
    if (!s)
        return 0;

    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        // Count the characters in the string.
    }
    return i;
}

/**
 * custom_strcmp - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int custom_strcmp(char *s1, char *s2)
{
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
    {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    }
    if (s1[i] == s2[i])
        return 0;
    else
        return (s1[i] < s2[i] ? -1 : 1);
}

/**
 * custom_starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next character of haystack or NULL
 */
char *custom_starts_with(const char *haystack, const char *needle)
{
    for (int i = 0; needle[i] != '\0'; i++)
    {
        if (needle[i] != haystack[i])
            return NULL;
    }
    return (char *)&haystack[i];
}

/**
 * custom_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *custom_strcat(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return ret;
}

