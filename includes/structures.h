/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   structures.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/27 19:58:10 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/27 20:05:31 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdint.h>

typedef struct	s_term
{
	int32_t	w;
	int32_t	h;
}
t_term;

typedef struct	s_pos
{
	uint32_t	x;
	uint32_t	y;
}
t_pos;

typedef struct	s_cmds
{
	char		**line;
	t_pos		curs;
	uint32_t	*top;
	uint32_t	*col;
	uint32_t	row;
	uint8_t		quote;
}
t_cmds;

typedef struct	s_escape_action
{
	char	*value;
	void	(*exec_action)(t_cmds *, uint32_t);
}
t_escape_action;

typedef struct	s_control_action
{
	char	value;
	void	(*exec_action)(t_cmds *, uint32_t);
}
t_control_action;


#endif
