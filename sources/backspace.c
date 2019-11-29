/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backspace.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 19:40:38 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/29 19:54:37 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

void	backspace(t_cmds *cmd)
{
	uint8_t		width;
	uint8_t		size;

	if (cmd->curs.byte)
	{
		get_utf8_prev_char_info(cmd->line[cmd->curs.y] + cmd->curs.byte, &width, &size);
		if (cmd->curs.byte == cmd->top[cmd->curs.y])
		{
			cmd->top[cmd->curs.y] -= size;
			cmd->curs.x -= width;
			cmd->curs.byte -= size;
			g_term.curs.x -= width;
			lt_move_n_left(width);
			lt_clear_end_of_line();
		}
		else
		{
			memmove(cmd->line[cmd->curs.y] + cmd->curs.byte - size,
					cmd->line[cmd->curs.y] + cmd->curs.byte, cmd->top[cmd->curs.y] - cmd->curs.byte);
			cmd->top[cmd->curs.y] -= size;
			cmd->curs.x -= width;
			cmd->curs.byte -= size;
			g_term.curs.x -= width;
			lt_move_n_left(width);
			lt_clear_end_of_line();
			write(STDOUT_FILENO, cmd->line[cmd->curs.y] + cmd->curs.byte, cmd->top[cmd->curs.y] - cmd->curs.byte);
			lt_move_cursor(g_term.curs.x, g_term.curs.y);
		}
	}
	return ;
}

