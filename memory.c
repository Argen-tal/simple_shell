#include "shell.h"

/**
 * bfree - frees a pointer and sets its value to NULL.
 * @ptr: the address of the pointer to free.
 *
 * Returns: 1 if the pointer was successfully freed, 0 otherwise.
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
