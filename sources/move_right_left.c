/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_right_left.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 13:37:00 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 10:43:23 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

void	lt_move_right(void)
{
	static char			*move = NULL;
	static unsigned int	len;

	if (!move)
	{
		if ((move = tgetstr("nd", NULL)) == NULL)
			return ;
		len = strlen(move);
	}
	write(2, move, len);
}

void	lt_move_n_right(int n)
{
	static char	*move = NULL;
	char		*command;

	if (!move)
	{
		if ((move = tgetstr("RI", NULL)) == NULL)
			return ;
	}
	command = tgoto(move, 0, n);
	write(2, command, strlen(command));
}

void	lt_move_left(void)
{
	static char			*move = NULL;
	static unsigned int	len;

	if (!move)
	{
		if ((move = tgetstr("le", NULL)) == NULL)
			return ;
		len = strlen(move);
	}
	write(2, move, len);
}

void	lt_move_n_left(int n)
{
	static char	*move = NULL;
	char		*command;

	if (!move)
	{
		if ((move = tgetstr("LE", NULL)) == NULL)
			return ;
	}
	command = tgoto(move, 0, n);
	write(2, command, strlen(command));
}
