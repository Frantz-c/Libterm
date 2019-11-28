/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 13:14:10 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 14:54:03 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

void	lt_move_cursor(int col, int row)
{
	static char	*move;
	char		*command;

	if (!move)
	{
		if ((move = tgetstr("cm", NULL)) == NULL)
			return ;
	}
	command = tgoto(move, col, row);
	write(2, command, strlen(command));
}

void	lt_move_cursor_home(void)
{
	static char			*move = NULL;
	static unsigned int	len;

	if (!move)
	{
		if ((move = tgetstr("ho", NULL)) == NULL)
			return ;
		len = strlen(move);
	}
	write(2, move, len);
}

void	lt_move_cursor_end(void)
{
	static char			*move = NULL;
	static unsigned int	len;

	if (!move)
	{
		if ((move = tgetstr("ll", NULL)) == NULL)
			return ;
		len = strlen(move);
	}
	write(2, move, len);
}
