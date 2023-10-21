#include "shell.h"

/**
 * check_interactive_mode - checks if the shell is running in interactive mode
 * 
 * This function checks whether the shell is running in interactive mode, which typically
 * means that the shell is being used in a way that allows user input and output, and provides
 * a command prompt for the user to enter commands.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * check_if_delimiter - checks if a character is a delimiter
 * @character: the character to check
 * @delimiter_string: the string of delimiters to compare against
 *
 * This function checks whether a given character is a delimiter, by comparing it against
 * a string of delimiters. If the character is found in the delimiter string, the function
 * returns 1. Otherwise, it returns 0.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - checks if a character is alphabetic
 * @character: the character to check
 *
 * This function checks whether a given character is an alphabetic character. If the character
 * is a letter in the alphabet (i.e., an uppercase or lowercase letter), the function returns 1.
 * Otherwise, it returns 0.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_string_to_int - converts a string to an integer
 * @string: the string to be converted
 *
 * This function converts a string of characters to an integer value. If the input string
 * contains no numbers, the function returns 0. Otherwise, the function returns the converted
 * integer value.
 *
 * Return: The converted integer value if successful, 0 otherwise.
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
