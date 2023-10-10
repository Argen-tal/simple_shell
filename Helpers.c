#include "shell.h"

/**
 * _strcmp - Compare two strings
 * @s1: The first string
 * @s2: The second string
 * Return: The difference between the first unmatched characters, or 0 if equal
 */
int _strcmp(const char *s1, const char *s2)                     {
    while (*s1 && *s2) /* Loop through both strings until null byte or mismatch */                                                  {
        if (*s1 != *s2) /* Check if characters are different */             return (*s1 - *s2); /* Return the difference between them */
        s1++; /* Increment pointer to next character in s1 */
        s2++; /* Increment pointer to next character in s2 */
    }
    return (*s1 - *s2); /* Return the difference between null bytes or last characters */
}
