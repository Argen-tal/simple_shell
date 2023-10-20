#include "shell.h"

/**
 * custom_strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow(char *str, char *d)
{
    int idx, token_idx, token_length, char_idx, num_tokens = 0;
    char **tokens;
    int i;

    if (str == NULL || str[0] == '\0')
        return NULL;

    if (!d)
        d = " ";

    for (idx = 0; str[idx] != '\0'; idx++)
    {
        if (!custom_is_delim(str[idx], d) && (custom_is_delim(str[idx + 1], d) || !str[idx + 1]))
            num_tokens++;
    }

    if (num_tokens == 0)
        return NULL;

    tokens = malloc((1 + num_tokens) * sizeof(char *));
    if (!tokens)
        return NULL;

    for (idx = 0, token_idx = 0; token_idx < num_tokens; token_idx++)
    {
        while (custom_is_delim(str[idx], d))
            idx++;

        token_length = 0;

        while (!custom_is_delim(str[idx + token_length], d) && str[idx + token_length])
            token_length++;

        tokens[token_idx] = malloc((token_length + 1) * sizeof(char));
        if (!tokens[token_idx])
        {
            for (i = 0; i < token_idx; i++)
                free(tokens[i]);
            free(tokens);
            return NULL;
        }

        for (char_idx = 0; char_idx < token_length; char_idx++)
            tokens[token_idx][char_idx] = str[idx++];

        tokens[token_idx][char_idx] = '\0';
    }
    tokens[token_idx] = NULL;

    return tokens;
}

/**
 * custom_strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow2(char *str, char d)
{
    int idx, token_idx, token_length, char_idx, num_tokens = 0;
    char **tokens;
    int i;

    if (str == NULL || str[0] == '\0')
        return NULL;

    for (idx = 0; str[idx] != '\0'; idx++)
    {
        if ((str[idx] != d && str[idx + 1] == d) ||
            (str[idx] != d && !str[idx + 1]) || str[idx + 1] == d)
            num_tokens++;
    }

    if (num_tokens == 0)
        return NULL;

    tokens = malloc((1 + num_tokens) * sizeof(char *));
    if (!tokens)
        return NULL;

    for (idx = 0, token_idx = 0; token_idx < num_tokens; token_idx++)
    {
        while (str[idx] == d && str[idx] != d)
            idx++;

        token_length = 0;

        while (str[idx + token_length] != d && str[idx + token_length] && str[idx + token_length] != d)
            token_length++;

        tokens[token_idx] = malloc((token_length + 1) * sizeof(char));
        if (!tokens[token_idx])
        {
            for (i = 0; i < token_idx; i++)
                free(tokens[i]);
            free(tokens);
            return NULL;
        }

        for (char_idx = 0; char_idx < token_length; char_idx++)
            tokens[token_idx][char_idx] = str[idx++];

        tokens[token_idx][char_idx] = '\0';
    }
    tokens[token_idx] = NULL;

    return tokens;
}

