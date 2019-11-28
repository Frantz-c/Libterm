/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   escape_actions.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/27 17:48:58 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 14:37:22 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

void	l_arrow(t_cmds *cmd)
{
	unsigned char	width;
	unsigned char	size;

	if (cmd->curs.byte > 0)
	{
		get_utf8_prev_char_info(cmd->line[cmd->curs.y] + cmd->curs.byte, &width, &size);
		cmd->curs.x -= width;
		g_term.curs.x -= width;
		lt_move_n_left(width);
		cmd->curs.byte -= size;
	}
}

void	u_arrow(t_cmds *cmd)
{
	return ;
}

void	d_arrow(t_cmds *cmd)
{
	return ;
}

void	r_arrow(t_cmds *cmd)
{
	unsigned char	width;
	unsigned char	size;

	if (cmd->top && cmd->curs.byte < cmd->top[cmd->curs.y])
	{
		get_utf8_char_info(cmd->line[cmd->curs.y] + cmd->curs.byte, &width, &size);
		cmd->curs.x += width;
		g_term.curs.x += width;
		lt_move_n_right(width);
		cmd->curs.byte += size;
	}
}

void	maj_right(t_cmds *cmd)
{
	return ;
}

void	maj_left(t_cmds *cmd)
{
	return ;
}

void	delete(t_cmds *cmd)
{
	return ;
}

void	escape(t_cmds *cmd)
{
	return ;
}

void	f1(t_cmds *cmd)
{
	return ;
}

void	f2(t_cmds *cmd)
{
	return ;
}
void	f3(t_cmds *cmd)
{
	return ;
}

void	f4(t_cmds *cmd)
{
	return ;
}
void	f5(t_cmds *cmd)
{
	return ;
}

void	f6(t_cmds *cmd)
{
	return ;
}
void	f7(t_cmds *cmd)
{
	return ;
}

void	f8(t_cmds *cmd)
{
	return ;
}
void	f9(t_cmds *cmd)
{
	return ;
}

void	f10(t_cmds *cmd)
{
	return ;
}

void	f12(t_cmds *cmd)
{
	return ;
}
