/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   escape_actions.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/27 17:48:58 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/27 20:49:07 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

void	l_arrow(t_cmds *cmd, uint32_t plen)
{
	if (cmd->curs.x > 0)
		cmd->curs.x--;
	lt_move_left();
	return ;
}

void	u_arrow(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	d_arrow(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	r_arrow(t_cmds *cmd, uint32_t plen)
{
	if (cmd->curs.x < cmd->top[cmd->curs.y])
		cmd->curs.x++;
	lt_move_right();
	return ;
}

void	maj_right(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	maj_left(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	delete(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	escape(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	f1(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	f2(t_cmds *cmd, uint32_t plen)
{
	return ;
}
void	f3(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	f4(t_cmds *cmd, uint32_t plen)
{
	return ;
}
void	f5(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	f6(t_cmds *cmd, uint32_t plen)
{
	return ;
}
void	f7(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	f8(t_cmds *cmd, uint32_t plen)
{
	return ;
}
void	f9(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	f10(t_cmds *cmd, uint32_t plen)
{
	return ;
}

void	f12(t_cmds *cmd, uint32_t plen)
{
	return ;
}
