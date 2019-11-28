/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_prompt.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 12:52:35 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 13:51:09 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

/*
**	PROMPT ESCAPE SEQUENCES
**	
**	%%	=	'%'
**	%M	=	hostname
**	%n	=	username
**
**	%?	=	last command return value
**	%d
**	%/	=	current directory path
**	%~	=	current directory path (with $HOME replacement)
**	%L	=	current value of $SHLVL
**
**	%D	=	current date.	for select a format: %D{string} (ex: %D{%d/%m/%y %H:%M:%S})
**	%T	=	current time.	24h format
**	%t	=	current time.	12h format
**
**	%B %b	=	bold start / end
**	%U %u	=	underline start / end
**	%F %f	=	color start / end	(ex: %F{blue,white} or %F{4,7}, %F{,2}, ...)
*/

uint32_t	print_prompt(const char *prompt, uint32_t len)
{
	write(1, prompt, len);
	g_term.curs.x += len;
	return (len);
}
