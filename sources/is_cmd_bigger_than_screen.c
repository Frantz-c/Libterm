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

uint8_t		is_cmd_bigger_than_screen(t_cmds *cmd)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	remaining_lines;
	uint32_t	max_width;
	uint32_t	line_width;

	remaining_lines = g_term.h;
	y = 0;
	while (y < cmd->n_row)
	{
		x = 0;
		while (x < cmd->len[y])
		{
			remaining_lines--;
			max_width = (x == 0) ? g_term.w - cmd->pad[y] : g_term.w;
			line_width = get_utf8_string_width2(cmd->line[y] + x, cmd->len[y] - x);
			if (remaining_lines == 0)
				return (line_width >= max_width) ? 1 : 0;
			x += get_utf8_string_size(cmd->line[y] + x, max_width, cmd->len[y] - x);
		}
		y++;
	}
	return (0);
}
