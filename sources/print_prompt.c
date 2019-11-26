/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_prompt.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 12:52:35 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 14:01:32 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

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
void	print_prompt(const char *prompt)
{

}
