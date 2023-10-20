#include "custom_shell.h"

/**
 * custom_input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t custom_input_buf(custom_info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) /* if nothing left in the buffer, fill it */
    {
        custom_free(*buf);
        *buf = NULL;
        signal(SIGINT, custom_sigintHandler);
#if CUSTOM_USE_GETLINE
        r = custom_getline(buf, &len_p, stdin);
#else
        r = custom_getline(info, buf, &len_p);
#endif
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0'; /* remove trailing newline */
                r--;
            }
            info->linecount_flag = 1;
            custom_remove_comments(*buf);
            custom_build_history_list(info, *buf, info->histcount++);
            /* if (custom_strchr(*buf, ';')) is this a command chain? */
            {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }
    return (r);
}

/**
 * custom_get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t custom_get_input(custom_info_t *info)
{
    static char *buf; /* the ';' command chain buffer */
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    custom_putchar(CUSTOM_BUF_FLUSH);
    r = custom_input_buf(info, &buf, &len);
    if (r == -1) /* EOF */
        return (-1);
    if (len)	/* we have commands left in the chain buffer */
    {
        j = i; /* init new iterator to the current buf position */
        p = buf + i; /* get a pointer for return */

        custom_check_chain(info, buf, &j, i, len);
        while (j < len) /* iterate to semicolon or end */
        {
            if (custom_is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* increment past the nulled ';'' */
        if (i >= len) /* reached the end of the buffer? */
        {
            i = len = 0; /* reset position and length */
            info->cmd_buf_type = CUSTOM_CMD_NORM;
        }

        *buf_p = p; /* pass back a pointer to the current command position */
        return (custom_strlen(p)); /* return the length of the current command */
    }

    *buf_p = buf; /* else not a chain, pass back the buffer from custom_getline() */
    return r; /* return the length of the buffer from custom_getline() */
}

/**
 * custom_read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t custom_read_buf(custom_info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return 0;
    r = read(info->readfd, buf, READ_BUF_SIZE);
    if (r >= 0)
        *i = r;
    return r;
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int custom_getline(custom_info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = custom_read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return (-1);

    c = custom_strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = custom_realloc(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? custom_free(p), -1 : -1);

    if (s)
        custom_strncat(new_p, buf + i, k - i);
    else
        custom_strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return s;
}

/**
 * custom_sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void custom_sigintHandler(__attribute__((unused))int sig_num)
{
    custom_puts("\n");
    custom_puts("$ ");
    custom_putchar(BUF_FLUSH);
}
