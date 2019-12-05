/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 16:24:03 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/04 18:19:02 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libterm.h"
#include "key_list.h"
#include <signal.h>
#include <stdint.h>
#include <fcntl.h>

#define LINE_MAX_LEN	0xffffu
#define CMD_MAX_LEN		0xffffu

// https://zestedesavoir.com/tutoriels/pdf/1733/termcap-et-terminfo.pdf
// https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/

// https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html#SEC7
// https://cirw.in/blog/bracketed-paste   http://www.xfree86.org/current/ctlseqs.html#Bracketed%20Paste%20Mode

int					debug;

t_term				g_term;

/*
**	insert character
*/
void	insert_char_from_cursor(t_cmds *cmd, const char *c, uint32_t csize)
{
	// insert character or add at end
	nalloc_if_needed(cmd, cmd->curs.y, csize);
	if (cmd->len[cmd->curs.y] != cmd->curs.x)	// insertion
	{
		memmove(cmd->line[cmd->curs.y] + cmd->curs.x + csize,
				cmd->line[cmd->curs.y] + cmd->curs.x,
				cmd->len[cmd->curs.y] - cmd->curs.x);
	}
	memcpy(cmd->line[cmd->curs.y] + cmd->curs.x, c, csize);
	cmd->len[cmd->curs.y] += csize;
}

void	free_cmd(t_cmds *cmd)
{
	unsigned int	i;

	i = 0;
	while (i < cmd->n_row)
	{
		free(cmd->line[i]);
		i++;
	}
	if (cmd->real_len)
		free(cmd->real_len);
	if (cmd->len)
		free(cmd->len);
	if (cmd->pad)
		free(cmd->pad);
	cmd->n_row = 0;
}

void	init_cmd(t_cmds *cmd, const char *prompt, uint32_t plen)
{
	cmd->prompt = prompt;
	cmd->plen = plen;
	cmd->n_row = 1;
	cmd->pasted = 0;
	cmd->curs = (t_pos){0, 0};
	cmd->origin_y = g_term.curs.y;

	cmd->line = malloc(sizeof(char *));
	cmd->real_len = malloc(sizeof(uint32_t));
	cmd->len = malloc(sizeof(uint32_t));
	cmd->pad = malloc(sizeof(uint32_t));
	cmd->prefix = malloc(sizeof(char *));
	if (!cmd->line || !cmd->real_len || !cmd->len || !cmd->pad || !cmd->prefix)
	{
		dprintf(STDERR_FILENO, "ERROR MALLOC 1\n");
		exit(1);
	}

	cmd->pad[0] = print_prompt(prompt, plen);
	cmd->len[0] = 0;
	cmd->real_len[0] = 0;
	cmd->line[0] = NULL;
	cmd->prefix[0] = NULL;
}


int		pasted_text(const char buf[], uint32_t len)
{
	if (len >= strlen(PASTE_START) && !memcmp(buf, PASTE_START, strlen(PASTE_START)))
		return (1);
	return (0);
}

void	write_char_to_cmd(t_cmds *cmd, const char *c, uint32_t csize)
{
	uint32_t	width;

	insert_char_from_cursor(cmd, c, csize);	// insert char in line
	print_cmd_from_cursor2(cmd);			// print the cmd
	dprintf(debug, "\n\n");
	cmd->curs.x += csize;
	width = get_utf8_char_width(c);
	if (g_term.curs.x + width == g_term.w)
	{
		g_term.curs.y++;
		g_term.curs.x = 0;
	}
	else if (g_term.curs.x + width > g_term.w)
	{
		g_term.curs.y++;
		g_term.curs.x = width;
	}
	else
		g_term.curs.x += width;
	dprintf(debug, "lt_move_cursor(%u, %u)\n", g_term.curs.x, g_term.curs.y);
	lt_move_cursor(g_term.curs.x, g_term.curs.y);
}

void	copy_and_display_input(t_cmds *cmd, const char buf[], uint32_t len)
{
	unsigned int	i;
	unsigned int	clen;

	i = 0;
	while (i < len)
	{
		clen = get_utf8_char_size(buf + i);
		write_char_to_cmd(cmd, buf + i, clen);
		i += clen;
	}
}

void	get_user_cmd(t_cmds *cmd)
{
	char		buf[READ_LEN];
	uint32_t	len;
	uint32_t	i;

	while (1)
	{
		len = read(STDIN_FILENO, buf, READ_LEN);
		i = 0;

		if (cmd->pasted)
		{
			// move cursor to paste start
			// re-print the pasted text only
			cmd->pasted = 0;
		}

		if (cmd->len[0] && buf[0] == ENTER)
		{
			// check quotes
//			if (cmd->quote)
//				...
//			else
				break;
		}
		
		// move in "execute_escape_sequence()"
		if (pasted_text(buf, len))
		{
			i = strlen(PASTE_START);
			len -= i;
			paste(buf + i, len, cmd);
			//print_paste
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
			if (buf[0] == CTRL_C) //faire qqch
				break;
//			printf("[execute_control()]\n");
			execute_control(cmd, buf[0]);
			continue ;
		}
		else if (len == 1u && buf[0] == BACKSPACE)
		{
//			printf("[backspace()]\n");
			backspace(cmd);
			continue ;
		}

//		printf("[copy_and_display_input()]\n");
		copy_and_display_input(cmd, buf, len);
	}
}


void	put_sigwinch(int sig)
{
	uint8_t		resized;
	t_2ddim		new_size;

	new_size.w = g_term.w;
	new_size.h = g_term.h;
	lt_get_terminal_size(&g_term);
	if (new_size.w != g_term.w)	
		resized |= W_RESIZED;
	if (new_size.h != g_term.h)
		resized |= H_RESIZED;
	new_size.w = g_term.w - new_size.w;
	new_size.h = g_term.h - new_size.h;

	if (resized & H_RESIZED)
	{
		g_term.curs.y += new_size.h;
		if (g_term.curs.y > 0x7ffffffu)
			g_term.curs.y = 0;
	}
	lt_move_cursor(g_term.curs.x, g_term.curs.y);
//	print_prompt_without_interpretation();
//	print_cmd_from_cursor();
}

void	put_sig(int sig)
{
	printf("SIGNAL IS %d\n", sig);
	close(debug);
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

	debug = open("debug", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (debug == -1)
		return (3);

	lt_terminal_mode(LT_NOECHO | LT_NOSIG);
	lt_enable_paste_mode();
//	lt_clear_screen();
//	lt_set_color(COLOR_CYAN, LT_NONE, LT_BOLD);
	lt_get_terminal_size(&g_term);
	lt_get_cursor_position(&g_term.curs.x, &g_term.curs.y);

	while (1)
	{
		init_cmd(&cmd, "( mhfc_42sh )>==] ", 18u);
		get_user_cmd(&cmd); // read user input
		i = 0;
		while (i < cmd.n_row)
		{
			printf("\nlaunch -> \"%.*s\"", (int)cmd.len[i], cmd.line[i]);
			fflush(stdout);
			g_term.curs.y++;
			i++;
		}
		free_cmd(&cmd);
		if (g_term.curs.y < (g_term.h - 1))
			g_term.curs.y++;
		g_term.curs.x = 0;
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
