/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 16:35:21 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 10:42:05 by fcordon     ###    #+. /#+    ###.fr     */
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

/*
	SIGWINCH ??
*/
int		lt_noecho_mode(void)
{
	static int	mode = -1;
	static struct termios	default_mode;
	static struct termios	noecho_mode;

	if (mode == -1)
	{
		if (tcgetattr(0, &default_mode) == -1)
			return (-1);
		noecho_mode = default_mode;
		//noecho_mode.c_iflag = IGNBRK | IGNCR;
		noecho_mode.c_lflag = 0;
		noecho_mode.c_cc[VMIN] = 1;
		noecho_mode.c_cc[VTIME] = 0;
	}
	if (mode)
	{
		tcsetattr(0, TCSANOW, &noecho_mode);
		return (mode = 0);
	}
	tcsetattr(0, TCSANOW, &default_mode);
	return (mode = 1);
}

void	lt_get_terminal_size(t_term *term)
{
	struct winsize	ws;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	term->w = ws.ws_col;
	term->h = ws.ws_row;
}
