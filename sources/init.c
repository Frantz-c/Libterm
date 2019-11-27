/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 16:35:21 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/27 18:07:49 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

int		lt_init(void)
{
	const char	*term = getenv("TERM");

	if (term == NULL)
		return (-2);
	return (tgetent(NULL, term));
}

int		lt_terminal_mode(uint32_t mode)
{
	static uint32_t			init = 0u;
	static struct termios	default_mode;
	static struct termios	noecho_mode;

	if (init == 0u)
	{
		if (tcgetattr(0, &default_mode) == -1)
			return (-1);
		//noecho_mode.c_iflag = IGNBRK | IGNCR;
		noecho_mode = default_mode;
		noecho_mode.c_cc[VTIME] = 0;
		init++;
	}
	if (mode & LT_NOECHO)
	{
		noecho_mode.c_cc[VMIN] = (mode & LT_NOBLOC) ? 0 : 1;
		noecho_mode.c_lflag = (mode & LT_NOSIG) ? 0 : ISIG;

		return (tcsetattr(0, TCSANOW, &noecho_mode));
	}
	else if (mode & LT_RESTORE)
		return (tcsetattr(0, TCSANOW, &default_mode));
	return (-2);
}

void	lt_get_terminal_size(t_term *term)
{
	struct winsize	ws;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	term->w = ws.ws_col;
	term->h = ws.ws_row;
}
