/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   string_is_too_large.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/02 14:17:25 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/02 16:50:17 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

extern int	debug;

uint32_t	is_cmd_too_large(t_cmds *cmd)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	rem_lines;
	uint32_t	row_width;

	rem_lines = g_term.h;
	j = 0;
	while (j < cmd->n_row)
	{
		if (rem_lines == 0)
		{
			dprintf(debug, "rem_lines = %u\n", rem_lines);
			return (1);
		}
		i = 0;
		while (i < cmd->len[j])
		{
			row_width = (i == 0) ? g_term.w - cmd->pad[j] : g_term.w;
			i += get_utf8_string_size(cmd->line[j] + i, row_width, cmd->len[j] - i);
			if (--rem_lines == 0)
				break ;
		}
		if (i < cmd->len[j])
		{
			dprintf(debug, "i = %u < %u\n", i, cmd->len[j]);
			return (1);
		}
		j++;
	}
	return (0);
}
