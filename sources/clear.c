/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 17:30:28 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/22 16:38:16 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

/*
**	clear screen and cursor home
*/
void	lt_clear_screen(void)
{
	static char			*s = NULL;
	static unsigned int	len = 0;

	if (!s)
	{
		if ((s = tgetstr("cl", NULL)) == NULL)
			return ;
		len = strlen(s);
	}
	write(2, s, len);
}

void	lt_clear_screen_from(void)
{
	static char			*s = NULL;
	static unsigned int	len = 0;

	if (!s)
	{
		if ((s = tgetstr("cd", NULL)) == NULL)
			return ;
		len = strlen(s);
	}
	write(2, s, len);
}

void	lt_clear_end_of_line(void)
{
	static char			*s = NULL;
	static unsigned int	len = 0;

	if (!s)
	{
		if ((s = tgetstr("ce", NULL)) == NULL)
			return ;
		len = strlen(s);
	}
	write(2, s, len);
}

void	lt_clear_n_char(int n)
{
	static char	*clear;
	char		*command;

	if (!clear)
	{
		if ((clear = tgetstr("ec", NULL)) == NULL)
			return ;
	}
	command = tgoto(clear, 0, n);
	write(2, command, strlen(command));
}
