/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   structures.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/27 19:58:10 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 13:47:21 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdint.h>

typedef struct	s_pos
{
	uint32_t	x;
	uint32_t	y;
}
t_pos;

typedef struct	s_term
{
	int32_t		w;
	int32_t		h;
	t_pos		curs;
}
t_term;

typedef struct	s_cmds
{
	char		**line;		// command
	t_pos		curs;		// cursor (dans la chaine)
	uint32_t	*len;		// longueur de la ligne (remplie)
	uint32_t	*real_len;	// longueur de la ligne (allouée)
	uint32_t	*pad;		// padding de la ligne
	const char	*prompt;	// prompt (avant interpretation)
	uint32_t	plen;		// longueur du prompt
	uint32_t	n_row;		// nombre de lignes
}
t_cmds;
/*
typedef struct	s_cmds
{
	char		**line;	// command
	t_curs_pos	curs;	// cursor
	uint32_t	*top;
	uint32_t	*col;
	uint32_t	*pad;
	const char	*prompt;
	uint32_t	plen;
	uint32_t	row;
	uint8_t		quote;
}
t_cmds;
*/
typedef struct	s_escape_action
{
	char	*value;
	void	(*exec_action)(t_cmds *);
}
t_escape_action;

typedef struct	s_control_action
{
	char	value;
	void	(*exec_action)(t_cmds *);
}
t_control_action;

#endif
