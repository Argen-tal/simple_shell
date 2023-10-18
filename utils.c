#include "shell.h"

/* _getenv: Get the value of an environment variable */
char *_getenv(const char *name, char **env) {
	int i;
	int len;

	len = strlen(name);
	for (i = 0; env[i] != NULL; i++) {
		if (strncmp(env[i], name, len) == 0 && env[i][len] == '=') {
			return (env[i] + len + 1);
		}
	}
	return (NULL);
}

/* _strlen: Get the length of a string */
size_t _strlen(const char *s) {
	size_t len;

	len = 0;
	while (*s != '\0') {
		len++;
		s++;
	}
	return (len);
}

/* _strcpy: Copy a string to another string */
char *_strcpy(char *dest, const char *src) {
	char *p;

	p = dest;
	while (*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (p);
}

/* _strcat: concatenates two strings */
char *_strcat(char *dest, const char *src) {
	char *p;

	p = dest;
	while (*dest != '\0') {
		dest++;
	}
	while (*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (p);
}

/**
* _strcmp - Compare two strings
* @s1: first string
* @s2: second string
* Return: difference between the first unmatched characters or 0 if equal
*/
int _strcmp(const char *s1, const char *s2) {
	while (*s1 && *s2) {
		if (*s1 != *s2) {
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

