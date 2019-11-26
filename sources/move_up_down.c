/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_up_down.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 13:28:04 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 10:43:47 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

void	lt_move_up(void)
{
	static char			*move = NULL;
	static unsigned int	len = 0;

	if (!move)
	{
		if ((move = tgetstr("up", NULL)) == NULL)
			return ;
		len = strlen(move);
	}
	write(2, move, len);
}

void	lt_move_n_up(int n)
{
	static char			*move = NULL;
	char				*command;

	if (!move)
	{
		if ((move = tgetstr("UP", NULL)) == NULL)
			return ;
	}
	command = tgoto(move, 0, n);
	write(2, command, strlen(command));
}

void	lt_move_down(void)
{
	static char			*move = NULL;
	static unsigned int	len;

	if (!move)
	{
		if ((move = tgetstr("do", NULL)) == NULL)
			return ;
		len = strlen(move);
	}
	write(2, move, len);
}

void	lt_move_n_down(int n)
{
	static char	*move = NULL;
	char		*command;

	if (!move)
	{
		if ((move = tgetstr("do", NULL)) == NULL)
			return ;
	}
	command = tgoto(move, 0, n);
	write(2, command, strlen(command));
}
