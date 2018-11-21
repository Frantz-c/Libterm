/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_options.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 19:15:20 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 12:04:19 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_options(t_options **opt)
{
	t_options	*tmp;
	t_options	*o;

	if ((o = *opt) == NULL)
		return ;
	tmp = NULL;
	while (o)
	{
		tmp = o->next;
		free(o);
		o = tmp;
	}
	*opt = NULL;
}
