#include "libterm.h"

char	*nalloc(char *ptr, uint32_t plen, uint32_t nlen)
{
	char	*new;

	if ((new = malloc(nlen)) == NULL)
	{
		dprintf(STDERR_FILENO, "[nalloc(%p, %u, %u)] Malloc error: exit\n", ptr, plen, nlen);
		exit(1);
	}
	if (ptr)
	{
		memcpy(new, ptr, (plen > nlen) ? nlen : plen);
		free(ptr);
	}
	return (new);
}

