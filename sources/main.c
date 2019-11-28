/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 16:24:03 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 14:59:34 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libterm.h"
#include "key_list.h"
#include <signal.h>
#include <stdint.h>

// https://zestedesavoir.com/tutoriels/pdf/1733/termcap-et-terminfo.pdf
// https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/

// https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html#SEC7
// https://cirw.in/blog/bracketed-paste   http://www.xfree86.org/current/ctlseqs.html#Bracketed%20Paste%20Mode


t_term				g_term;


void	free_cmd(t_cmds *cmd)
{
	unsigned int	i;

	i = 0;
	while (i < cmd->row)
	{
		free(cmd->line[i]);
		i++;
	}
	if (cmd->col)
		free(cmd->col);
	if (cmd->top)
		free(cmd->top);
	if (cmd->pad)
		free(cmd->pad);
	cmd->row = 0;
}

void	init_cmd(t_cmds *cmd, const char *prompt, uint32_t plen)
{
	cmd->prompt = prompt;
	cmd->row = 0;
	cmd->col = NULL;
	cmd->line = NULL;
	cmd->top = NULL;
	cmd->pad = malloc(sizeof(uint32_t));
	cmd->pad[0] = print_prompt(prompt, plen);
	cmd->curs = (t_curs_pos){0, 0, 0};
	cmd->quote = 0;
}

char	*nalloc(char *ptr, uint32_t plen, uint32_t nlen)
{
	char	*new;

	if ((new = malloc(nlen)) == NULL)
	{
		dprintf(STDERR_FILENO, "[nalloc(%p, %u, %u)] Malloc error: exit\n", ptr, plen, nlen);
		exit(1);
	}
	if (ptr)
	{
		memcpy(new, ptr, (plen > nlen) ? nlen : plen);
		free(ptr);
	}
	return (new);
}

int		pasted_text(const char buf[], uint32_t len)
{
	if (len > strlen(PASTE_START) && !memcmp(buf, PASTE_START, len))
		return (1);
	return (0);
}

void	paste(const char buf[], uint32_t len, t_cmds *cmd)
{
	return ;
}

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

void	erase_previous_char(t_cmds *cmd)
{
	return ;
}

/*
	typedef struct	s_cmds
	{
		char		*prompt;
		char		**line;
		t_pos		curs;
		uint32_t	*top;
		uint32_t	*col;
		uint32_t	row;
		uint32_t	plen;
		uint8_t		quote;
	}
	t_cmds;
*/

void	write_char_to_cmd(t_cmds *cmd, const char *buf, uint32_t clen)
{
	unsigned int	add;

	if (cmd->line == NULL)
	{
		cmd->line = malloc(sizeof(char *));
		cmd->col = malloc(sizeof(uint32_t));
		cmd->top = malloc(sizeof(uint32_t));
		if (!cmd->line || !cmd->col || !cmd->top)
		{
			dprintf(STDERR_FILENO, "ERROR MALLOC 1\n");
			exit(1);
		}
		cmd->col[cmd->curs.y] = 0;
		cmd->line[cmd->curs.y] = NULL;
		cmd->row = 1;
	}

	if (clen > (cmd->col[cmd->curs.y] - cmd->top[cmd->curs.y]))
	{
//		printf("[nalloc()]\n");
		add = (g_term.w > clen) ? g_term.w : clen + g_term.w;
		cmd->line[cmd->curs.y] = nalloc(cmd->line[cmd->curs.y], cmd->col[cmd->curs.y],
										cmd->col[cmd->curs.y] + add);
	}

	uint8_t		width;
	// add characters
	if (cmd->curs.byte == cmd->top[cmd->curs.y])
	{
//		printf("[add_characters]\n");
		// write to the buffer
		memcpy(cmd->line[cmd->curs.y] + cmd->curs.byte, buf, clen);
		cmd->curs.byte += clen;
		cmd->top[cmd->curs.y] += clen;
		width = get_utf8_string_width2(buf, clen);
		cmd->curs.x += width;
		g_term.curs.x += width;

		write(STDOUT_FILENO, buf, clen);	// display characters
	}
	// insert characters
	else
	{
//		printf("[insert_characters]\n");
		memmove(cmd->line[cmd->curs.y] + cmd->curs.byte + clen, cmd->line[cmd->curs.y] + cmd->curs.byte,
				cmd->top[cmd->curs.y] - cmd->curs.byte);
		memcpy(cmd->line[cmd->curs.y] + cmd->curs.byte, buf, clen);
		cmd->top[cmd->curs.y] += clen;
		lt_clear_end_of_line();
		write(STDOUT_FILENO, cmd->line[cmd->curs.y] + cmd->curs.byte, cmd->top[cmd->curs.y] - cmd->curs.byte);
		width = get_utf8_string_width2(buf, clen);
		cmd->curs.x += width;
		g_term.curs.x += width;
		cmd->curs.byte += clen;
		lt_move_cursor(g_term.curs.x, g_term.curs.y);
	}
}

void	copy_and_display_input(t_cmds *cmd, const char buf[], uint32_t len)
{
	unsigned int	i;
	unsigned int	clen;

	i = 0;
	while (i < len)
	{
		if (buf[i] == '`' && (cmd->quote & SQUOTE) == 0)
		{
			cmd->quote ^= BQUOTE;
		}
		else if (buf[i] == '\'' && (cmd->quote & DQUOTE) == 0)
		{
			cmd->quote ^= SQUOTE;
		}
		else if (buf[i] == '"' && (cmd->quote & SQUOTE) == 0)
		{
			cmd->quote ^= DQUOTE;
		}
		clen = get_utf8_char_size(buf + i);
//		printf("[clen = %u && write_char_to_cmd()]\n", clen);
		write_char_to_cmd(cmd, buf + i, clen);
		i += clen;
	}
}

void	get_user_cmd(t_cmds *cmd)
{
	char			buf[READ_LEN];
	uint32_t	len;
	uint32_t	i;

	while (1)
	{
		len = read(STDIN_FILENO, buf, READ_LEN);
		i = 0;

		if (len == 1 && buf[0] == '\n')
		{
			if (cmd->quote)
			{
				write_char_to_cmd(cmd, "<quote>", 7u);
			}
			else
				break;
		}
		
//		printf("[pasted_text()]\n");
		// move in "execute_escape_sequence()"
		if (pasted_text(buf, len))
		{
			i = strlen(PASTE_START);
			len -= i;
			paste(buf + i, len, cmd);
			continue ;
		}

		uint32_t	j = 0;
		uint32_t	clen;
		while (j < len)
		{
//			printf("[secure_get_utf8_char_size()]\n");
			if ((clen = secure_get_utf8_char_size(buf + j, len - j)) == 0)
				buf[j++] = '?';
			else
				j += clen;
		}

		if (buf[0] == '\e')
		{
//			printf("[execute_escape_sequence()]\n");
			if (execute_escape_sequence(cmd, buf, &len))
				continue ;
		}
		else if (len == 1u && buf[0] > 0 && buf[0] < 27 && buf[0] != '\n'
				&& buf[0] != '\r' && buf[0] != 17 && buf[0] != 19)
		{
			if (buf[0] == CTRL_C)
			{
				free_cmd(cmd);
				break;
			}
//			printf("[execute_control()]\n");
			execute_control(cmd, buf[0]);
			continue ;
		}
		else if (len == 1u && buf[0] == BACKSPACE)
		{
//			printf("[erase_previous_char()]\n");
			erase_previous_char(cmd);
			continue ;
		}

//		printf("[copy_and_display_input()]\n");
		copy_and_display_input(cmd, buf, len);
	}
}


void	put_sigwinch(int sig)
{
	printf(" { window resized }\n");
	lt_get_terminal_size(&g_term);
}

void	put_sig(int sig)
{
	printf("SIGNAL IS %d\n", sig);
	lt_terminal_mode(LT_RESTORE);
	exit(0);
}
/*
int		get_key(const char *k, uint32_t *index)
{
	for (uint32_t i = 0; button[i].name; i++)
	{
		if (strcmp(button[i].value, k) == 0)
		{
			write(1, button[i].name, strlen(button[i].name));
			*index = i;
			return (1);
		}
	}
	return (0);
}
*/
int		main(void)
{
	t_cmds		cmd;
	uint32_t	i;

	if (lt_init() != 1)
	{
		fprintf(stderr, "can't initialise libterm\n");
		return (1);
	}

	for (i = 0; i < 33; i++)
		signal(i, put_sig);

	signal(SIGWINCH, put_sigwinch);


	lt_terminal_mode(LT_NOECHO | LT_NOSIG);
	lt_enable_paste_mode();
	lt_clear_screen();
	lt_set_color(COLOR_CYAN, LT_NONE, LT_BOLD);
	lt_get_terminal_size(&g_term);
	g_term.curs = (t_pos){0, 0};

	while (1)
	{
		init_cmd(&cmd, "( mhfc_42sh )>==] ", 18u);
		get_user_cmd(&cmd); // read user input
		i = 0;
		while (i < cmd.row)
		{
			printf("\nlaunch -> \"%s\"", cmd.line[i]);
			fflush(stdout);
			g_term.curs.y++;
			free(cmd.line[i]);
			i++;
		}
		if (cmd.row)
		{
			free(cmd.line);
			free(cmd.col);
			free(cmd.top);
		}
		if (g_term.curs.y < (g_term.h - 1))
			g_term.curs.y++;
		g_term.curs.x = 0;
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
