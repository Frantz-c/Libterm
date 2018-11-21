/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/22 19:00:11 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 17:15:36 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
/*
static char	*int_to_ascii(t_uint n, char *s, int negative)
{
	while (1)
	{
		*(--s) = (n % 10) + 48;
		n /= 10;
		if (!n)
			break ;
	}
	if (negative)
		*(--s) = '-';
	return (s);
}

char		*ft_itoa(int n)
{
	int		negative;
	t_uint	number;
	char	tmp[13];

	tmp[12] = '\0';
	if (n < 0)
	{
		negative = 1;
		number = (t_uint)~n + 1;
	}
	else
	{
		number = (t_uint)n;
		negative = 0;
	}
	return (ft_strdup(int_to_ascii(number, tmp + 12, negative)));
}
*/
char		*ft_itoa(int n)
{
	return (ft_ltoa(n));
}
