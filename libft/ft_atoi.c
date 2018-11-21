/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 15:35:54 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 11:49:27 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
/*
static int			is_num(char c)
{
	return (c > 47 && c < 58);
}

static int			is_space(char c)
{
	return ((c > 8 && c < 14) || c == 32);
}

static const char	*left_trim(const char *s, int *negative)
{
	*negative = 0;
	while (is_space(*s))
		s++;
	if (is_num(*s))
		return (s);
	if (*s == '+')
	{
		s++;
		if (!is_num(*s))
			return (NULL);
	}
	else if (*s == '-')
	{
		s++;
		if (!is_num(*s))
			return (NULL);
		*negative = 1;
	}
	return (s);
}

static int			ft_strtoi(const char *s, int negative)
{
	unsigned int	n;

	n = 0;
	while (is_num(*s))
	{
		n *= 10;
		n += *(s++) - 48;
	}
	return ((negative) ? (int)(~n + 1) : (int)n);
}

int					ft_atoi(const char *s)
{
	int	negative;

	if ((s = left_trim(s, &negative)) == NULL)
		return (0);
	return (ft_strtoi(s, negative));
}
*/
extern inline int	ft_atoi(const char *s)
{
	return ((int)ft_atol(s));
}
