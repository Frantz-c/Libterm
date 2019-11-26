/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_delete_char.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 14:48:23 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 10:48:26 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

/* 
** don't move cursor in insert mode ??
*/
void	lt_insert_mode_on(void)
{
	static char			*insert;
	static unsigned int	len;

	if (!insert)
	{
		if ((insert = tgetstr("im", NULL)) == NULL)
			return ;
		len = strlen(insert);
	}
	write(2, insert, len);
}

void	lt_insert_mode_off(void)
{
	static char			*insert;
	static unsigned int	len;

	if (!insert)
	{
		if ((insert = tgetstr("ei", NULL)) == NULL)
			return ;
		len = strlen(insert);
	}
	write(2, insert, len);
}

void	lt_insert_n_blank_char(int n)
{
	static char			*insert = NULL;
	static char			*insert2 = NULL;
	static unsigned int len = 0;
	char				*command;

	if (!len)
	{
		if ((insert = tgetstr("IC", NULL)) == NULL)
		{
			if ((insert2 = tgetstr("ic", NULL)) == NULL)
				return ;
			len = strlen(insert2);
		}
		else
			len = 1;
	}
	if (insert)
	{
		command = tgoto(insert, 0, n);
		write(2, command, strlen(command));
	}
	else if (insert2)
		while (n--)
			write(2, insert2, len);
}

void	lt_insert_blank_char(void)
{
	static char			*insert = NULL;
	static unsigned int	len;

	if (!insert)
	{
		if ((insert = tgetstr("ic", NULL)) == NULL)
			return ;
		len = strlen(insert);
	}
	write(2, insert, len);
}

/*
** if size is 0, function use ft_strlen
*/
void	lt_insert_string_at(const char *s, unsigned int size)
{
	if (size == 0)
		size = strlen(s);
	lt_insert_mode_on();
	lt_insert_n_blank_char((int)size);
	printf("%s", s);
//	move_n_right(utf8_strlen(s));
	lt_insert_mode_off();
}
