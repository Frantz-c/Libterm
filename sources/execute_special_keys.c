/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute_special_keys.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 18:55:34 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 18:57:42 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

uint32_t	execute_escape_sequence(t_cmds *cmd, char *buf, uint32_t *len)
{
	static const t_escape_action 	l_escape[] = {
		{L_ARROW, &l_arrow}, {U_ARROW, &u_arrow}, {D_ARROW, &d_arrow}, {R_ARROW, &r_arrow},
		{MAJ_RIGHT, &maj_right}, {MAJ_LEFT, &maj_left},
		{DELETE, &delete}, {ESCAPE, &escape},
		{F1, &f1}, {F2, &f2}, {F3, &f3}, {F4, &f4},
		{F5, &f5}, {F6, &f6}, {F7, &f7}, {F8, &f8},
		{F9, &f9}, {F10, &f10}, {F12, &f12},
		{NULL, NULL}
	};
	uint32_t	i;

	i = 0;
	while (l_escape[i].value)
	{
		if (*len == strlen(l_escape[i].value) && memcmp(l_escape[i].value, buf, *len) == 0)
		{
			l_escape[i].exec_action(cmd);
			return (1);
		}
		i++;
	}

	// inutile ?
	i = 0;
	while (buf[i] == '\e')
	{
		i++;
		if (i == *len)
		{
			*len = 0;
			return (0);
		}
	}
	*len -= i;
	memmove(buf, buf + i, *len);
	return (0);
}

void	execute_control(t_cmds *cmd, char c)
{
	static const t_control_action 	control[] = {
		{CTRL_A, &ctrl_a}, {CTRL_B, &ctrl_b}, {CTRL_C, &ctrl_c}, {CTRL_D, &ctrl_d},
		{CTRL_E, &ctrl_e}, {CTRL_F, &ctrl_f}, {CTRL_G, &ctrl_g}, {CTRL_H, &ctrl_h},
		{CTRL_I, &ctrl_i}, {CTRL_K, &ctrl_k}, {CTRL_L, &ctrl_l}, {CTRL_N, &ctrl_n},
		{CTRL_O, &ctrl_o}, {CTRL_P, &ctrl_p}, {CTRL_R, &ctrl_r}, {CTRL_T, &ctrl_t},
		{CTRL_U, &ctrl_u}, {CTRL_V, &ctrl_v}, {CTRL_W, &ctrl_w}, {CTRL_X, &ctrl_x},
		{CTRL_Y, &ctrl_y}, {CTRL_Z, &ctrl_z}, {0, NULL}
	};
	uint32_t	i;

	i = 0;
	while (control[i].value)
	{
		if (control[i].value == c)
		{
			control[i].exec_action(cmd);
			return ;
		}
		i++;
	}
}
