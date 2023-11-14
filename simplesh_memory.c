#include "shell.h"

/**
 * mem_free - function that frees a pointer and NULLs the address
 * @poiter: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int mem_free(void **poiter)
{
	if (poiter && *poiter)
	{
		free(*poiter);
		*poiter = NULL;
		return (1);
	}
	return (0);
}
