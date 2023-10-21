#include "shell.h"

/**
 * _strncpy - Copy a string to a specified length
 *
 * @dest: The destination string to copy to
 * @src: The source string to copy from
 * @n: The number of characters to copy
 *
 * Return: The resulting concatenated string.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncpy - Copy a string to a specified length
 *
 * @dest: The destination string to copy to
 * @src: The source string to copy from
 * @n: The number of characters to copy
 *
 * Return: The resulting concatenated string.
 *
 * Description: The function copies up to `n`
 * characters from the source string
 * `src` to the destination string `dest`.
 * If the length of `src` is less than
 * `n`, the remainder of `dest` will be
 * filled with null characters ('\0').
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
