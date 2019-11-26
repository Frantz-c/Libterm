/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_delete.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 14:33:30 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 10:47:33 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

void	lt_insert_line_before(void)
{
	static char			*insert = NULL;
	static unsigned int	len;

	if (!insert)
	{
		if ((insert = tgetstr("al", NULL)) == NULL)
			return ;
		len = strlen(insert);
	}
	write(2, insert, len);
}

void	lt_insert_n_lines_before(int n)
{
	static char	*insert = NULL;
	char		*command;

	if (!insert)
	{
		if ((insert = tgetstr("AL", NULL)) == NULL)
			return ;
	}
	command = tgoto(insert, 0, n);
	write(2, command, strlen(command));
}

void	lt_delete_current_line(void)
{
	static char			*delete = NULL;
	static unsigned int	len;

	if (!delete)
	{
		if ((delete = tgetstr("dl", NULL)) == NULL)
			return ;
		len = strlen(delete);
	}
	write(2, delete, len);
}

void	lt_delete_n_lines_from(int n)
{
	static char	*delete= NULL;
	char		*command;

	if (!delete)
	{
		if ((delete = tgetstr("DL", NULL)) == NULL)
			return ;
	}
	command = tgoto(delete, 0, n);
	write(2, command, strlen(command));
}
