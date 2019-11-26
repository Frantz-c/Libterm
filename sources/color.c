/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   color.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 12:53:51 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 15:02:16 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

void	lt_set_color(int color1, int color2, int video_mode)
{
	static const char	*fg = NULL;
	static const char	*bg = NULL;
	static const char	*mode = NULL;
	char				*cmd;

	if (!fg)
	{
		if ((fg = tgetstr("AF", NULL)) == NULL ||
				((bg = tgetstr("AB", NULL)) == NULL))
			return ;
	}
	if (color1 != LT_NONE)
		cmd = tgoto(fg, 0, color1);
	write(2, cmd, strlen(cmd));
	if (color2 != LT_NONE)
		cmd = tgoto(bg, 0, color2);
	write(2, cmd, strlen(cmd));
	if (video_mode != LT_NONE)
		cmd = tgoto(mode, 0, video_mode);
	write(2, cmd, strlen(cmd));
}

void	lt_reset_color(void)
{
	static const char	*reset = NULL;

	if (!reset)
	{
		if ((reset = tgetstr("me", NULL)) == NULL)
			return ;
	}

}

void	lt_set_fg_color(int color)
{
	static const char	*fg = NULL;
	char				*cmd;

	if (!fg)
	{
		if ((fg = tgetstr("AF", NULL)) == NULL)
			return ;
	}
	cmd = tgoto(fg, 0, color);
	write(2, cmd, strlen(cmd));
}

void	lt_set_bg_color(int color)
{
	static const char	*bg = NULL;
	char				*cmd;

	if (!bg)
	{
		if ((bg = tgetstr("AM", NULL)) == NULL)
			return ;
	}
	cmd = tgoto(bg, 0, color);
	write(2, cmd, strlen(cmd));
}

void	lt_set_video_mode(int mode)
{
	static const char *const	cap = {
		"mb", "us", "mb", "mh", "mk", "mp", "mr"
	};
	static const char			*modes[] = {NULL};
	unsigned int				i;
	unsigned int				b;

	i = 0;
	b = 1u;
	while (i != 7)
	{
		if ((mode & b) && modes[i] == NULL)
		{
			if ((modes[i] = tgetstr(cap[i], NULL)) == NULL)
			{
				i++;
				b <<= 1;
				continue ;
			}
		}
		write(2, modes[i], strlen(modes[i]));
		i++;
		b <<= 1;
	}
}
