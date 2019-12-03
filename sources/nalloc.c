#include "libterm.h"

void	*nalloc(void *ptr, uint32_t plen, uint32_t nlen, size_t elem_size)
{
	void	*new;

	if ((new = malloc(nlen * elem_size)) == NULL)
	{
		dprintf(STDERR_FILENO, "[nalloc(%p, %u, %u)] Malloc error: exit\n", ptr, plen, nlen);
		exit(1);
	}
	if (ptr)
	{
		memcpy(new, ptr, (plen > nlen) ? nlen * elem_size : plen * elem_size);
		free(ptr);
	}
	return (new);
}

int		nalloc_if_needed(t_cmds *cmd, uint32_t y, uint32_t size)
{
	uint32_t	add;

	//printf("cmd = %p, cmd->line[%u] = %p\n", cmd, y, cmd->line[y]);
	if (size > (cmd->real_len[y] - cmd->len[y]))
	{
		add = (g_term.w > size) ? g_term.w : size + g_term.w;
		cmd->line[y] = nalloc
		(
			cmd->line[y],
			cmd->real_len[y],
			cmd->real_len[y] + add,
			sizeof(char)
		);
	}
	return (0);
}
