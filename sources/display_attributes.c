/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_attributes.c                             .::    .:/ .      .::   */
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
	if (color1 != LT_NONE)
		lt_set_fg_color(color1);
	if (color2 != LT_NONE)
		lt_set_bg_color(color2);
	if (video_mode != LT_NONE)
		lt_set_video_mode(video_mode);
}

void	lt_reset_color(void)
{
	static const char	*reset = NULL;
	static unsigned int	len;

	if (!reset)
	{
		if ((reset = tgetstr("me", NULL)) == NULL)
			return ;
		len = strlen(reset);
	}
	write(2, reset, len);
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
		if ((bg = tgetstr("AB", NULL)) == NULL)
			return ;
	}
	cmd = tgoto(bg, 0, color);
	write(2, cmd, strlen(cmd));
}

void	lt_set_video_mode(int mode)
{
	static char		*cap[7] = {
		"md", "us", "mb", "mh", "mk", "mp", "mr"
	};
	static char		*modes[7] = {NULL};
	unsigned int	i;
	unsigned int	b;

	i = 0;
	b = 1u;
	while (b != LT_MODE_END)
	{
		if ((mode & b))
		{
			if (modes[i] == NULL)
			{
				if ((modes[i] = tgetstr(cap[i], NULL)) != NULL)
					write(2, modes[i], strlen(modes[i]));
			}
			else
				write(2, modes[i], strlen(modes[i]));
		}
		i++;
		b <<= 1;
	}
}
