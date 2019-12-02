/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 16:24:03 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/29 19:46:57 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libterm.h"
#include "key_list.h"
#include <signal.h>
#include <stdint.h>
#include <fcntl.h>

#define LINE_MAX_LEN
#define CMD_MAX_LEN

// https://zestedesavoir.com/tutoriels/pdf/1733/termcap-et-terminfo.pdf
// https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/

// https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html#SEC7
// https://cirw.in/blog/bracketed-paste   http://www.xfree86.org/current/ctlseqs.html#Bracketed%20Paste%20Mode

int					debug;

t_term				g_term;

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

int		nalloc_if_needed(t_cmds *cmd, uint32_t size)
{
	uint32_t	add;

	if (size > (cmd->real_len[cmd->curs.y] - cmd->len[cmd->curs.y]))
	{
		add = (g_term.w > size) ? g_term.w : size + g_term.w;
		cmd->line[cmd->curs.y] = nalloc
		(
			cmd->line[cmd->curs.y],
			cmd->real_len[cmd->curs.y],
			cmd->real_len[cmd->curs.y] + add
		);
	}
	return (0);
}

/*
**	print the command but don't care of
**	the cursor's position after execution
*/
void	print_cmd_from_cursor2(t_cmds *cmd)
{
	uint32_t	line_width;
	uint32_t	line_size;
	uint32_t	line_start;
	uint32_t	i;
	uint32_t	j;
	uint32_t	k;

	i = cmd->curs.y;
	k = 0;
	while (i < cmd->n_row)
	{
		line_start = (i == 0) ? cmd->curs.x : 0;
		j = 0;
		dprintf(debug, "line_start = %u < cmd->len[%u] = %u\n", line_start, i, cmd->len[i]);
		while (line_start < cmd->len[i])
		{
			(j == 0) ? lt_move_cursor((i == 0) ? g_term.curs.x : cmd->pad[i], g_term.curs.y + k) :
						lt_move_cursor(0, cmd->origin_y + j + k);

			uint32_t x, y;
			lt_get_cursor_position(&x, &y);
			dprintf(debug, "real cursor position = {%u, %u}\n", x, y);

			line_width = (j == 0) ? g_term.w - cmd->pad[i] : g_term.w;
			line_size = get_utf8_string_size(cmd->line[i] + line_start,
										line_width, cmd->len[i] - line_start);
			dprintf(debug, "get_...(\"%.*s\"), line_size = %u\n",
					cmd->len[i] - line_start, cmd->line[i] + line_start, line_size);
			lt_clear_end_of_line();
			dprintf(debug, "line_size = %u : write \"%.*s\"\n",
					line_size, line_size, cmd->line[i] + line_start);
			write(STDOUT_FILENO, cmd->line[i] + line_start, line_size);
			line_start += line_size;
			j++;
		}
		k += j;
		i++;
	}
}


/*
**	insert character
*/
void	insert_char_from_cursor(t_cmds *cmd, const char *c, uint32_t csize)
{
	// insert character or add at end
	nalloc_if_needed(cmd, csize);
	if (cmd->len[cmd->curs.y] != cmd->curs.x)	// insertion
	{
		memmove(cmd->line[cmd->curs.y] + cmd->curs.x + csize,
				cmd->line[cmd->curs.y] + cmd->curs.x,
				cmd->len[cmd->curs.y] - cmd->curs.x);
	}
	memcpy(cmd->line[cmd->curs.y] + cmd->curs.x, c, csize);
	cmd->len[cmd->curs.y] += csize;
}

void	print_cmd(t_cmds *cmd)
{
//	uint32_t	nlines;
	uint32_t	line_width;
	uint32_t	line_size;
	uint32_t	line_start;
	uint32_t	i;
	uint32_t	j;
	uint32_t	k;

	i = 0;
	k = 0;
	while (i < cmd->n_row)
	{
//		nlines = ((cmd->len[i] + plen) / g_term.w)
//				+ ((cmd->len[i] + plen) % g_term.w);
		line_start = 0;
		j = 0;
		while (line_start < cmd->len[i])
		{
			(j == 0) ? lt_move_cursor(cmd->pad[i], cmd->origin_y + k) :
						lt_move_cursor(0, cmd->origin_y + j + k);
			line_width = (j == 0) ? g_term.w - cmd->pad[i] : g_term.w;
			line_size = get_utf8_string_size(cmd->line[i] + line_start,
										line_width, cmd->len[i] - line_start);
			lt_clear_end_of_line();
			write(STDOUT_FILENO, cmd->line[i] + line_start, line_size);
			line_start += line_size;
			j++;
		}
		k += j;
		i++;
	}
	lt_move_cursor(g_term.curs.x, g_term.curs.y);
}

void	print_cmd_from_cursor(t_cmds *cmd)
{
	uint32_t	line_width;
	uint32_t	line_size;
	uint32_t	line_start;
	uint32_t	i;
	uint32_t	j;
	uint32_t	k;

	i = cmd->curs.y;
	k = 0;
	while (i < cmd->n_row)
	{
		line_start = (i == 0) ? cmd->curs.x : 0;
		j = 0;
		while (line_start < cmd->len[i])
		{
			(j == 0) ? lt_move_cursor(cmd->pad[i], cmd->origin_y + k) :
						lt_move_cursor(0, cmd->origin_y + j + k);
			line_width = (j == 0) ? g_term.w - cmd->pad[i] : g_term.w;
			line_size = get_utf8_string_size(cmd->line[i] + line_start,
										line_width, cmd->len[i] - line_start);
			lt_clear_end_of_line();
			dprintf(debug, "line_size = %u : write \"%.*s\"\n",
					line_size, line_size, cmd->line[i] + line_start);
			write(STDOUT_FILENO, cmd->line[i] + line_start, line_size);
			line_start += line_size;
			j++;
		}
		k += j;
		i++;
	}
	lt_move_cursor(g_term.curs.x, g_term.curs.y);

}
/*
void	print_cmd_region()
{
	
}
*/
void	move_cursors_right(t_cmds *cmd, uint8_t width, uint8_t size)
{
	cmd->curs.x += size;
	g_term.curs.x += width;
	lt_move_n_right(width);
}

void	move_cursors_left(t_cmds *cmd, uint8_t width, uint8_t size)
{
	cmd->curs.x -= size;
	g_term.curs.x -= width;
	lt_move_n_left(width);
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
	if (!cmd->line || !cmd->real_len || !cmd->len || !cmd->pad)
	{
		dprintf(STDERR_FILENO, "ERROR MALLOC 1\n");
		exit(1);
	}

	cmd->pad[0] = print_prompt(prompt, plen);
	cmd->len[cmd->curs.y] = 0;
	cmd->line[cmd->curs.y] = NULL;
}


int		pasted_text(const char buf[], uint32_t len)
{
	if (len >= strlen(PASTE_START) && !memcmp(buf, PASTE_START, strlen(PASTE_START)))
		return (1);
	return (0);
}

void	paste(char buf[], uint32_t len, t_cmds *cmd)
{
	char		tmp[8];
	uint32_t	i;
	uint8_t		end;
	uint32_t	paste_pos;

	end = 0;
	paste_pos = cmd->curs.x;
	cmd->pasted_byte = cmd->curs.x;
	cmd->pasted_pos = g_term.curs.x;

	// if buf == "\e[200~"
	if (len == 0)
		len = read(STDIN_FILENO, buf, READ_LEN - strlen(PASTE_START));

	while (1)
	{
		i = len - 1;
		while (i != 0xffffffffu)
		{
			if (buf[i] == '\e')
			{
				if (memcmp(PASTE_END, buf + i, strlen(PASTE_END)) == 0)
				{
					if (i != 0)
					{
						nalloc_if_needed(cmd, i);
						memcpy(cmd->line[cmd->curs.y] + cmd->curs.x, buf, i);
						cmd->len[cmd->curs.y] += i;
						cmd->curs.x += i;
					}
					end = 1;
					break ;
				}
			}
			i--;
		}
		if (end == 1)
		{
			lt_set_video_mode(LT_REVERSE);
			write(STDOUT_FILENO,
				cmd->line[cmd->curs.y] + paste_pos,
				cmd->len[cmd->curs.y] - paste_pos
			);
			lt_reset_color();
			g_term.curs.x += cmd->curs.x - paste_pos;
			break ;
		}
		nalloc_if_needed(cmd, len);
		memcpy(cmd->line[cmd->curs.y] + cmd->curs.x, buf, len);
		cmd->len[cmd->curs.y] += len;
		cmd->curs.x += len;

		len = read(STDIN_FILENO, buf, READ_LEN - strlen(PASTE_START));
	}
	cmd->pasted = 1;
}

void	write_char_to_cmd(t_cmds *cmd, const char *c, uint32_t csize)
{
	uint32_t	width;

	insert_char_from_cursor(cmd, c, csize);	// insert char in line
	print_cmd_from_cursor2(cmd);			// print the cmd
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
	dprintf(debug, "g_term.curs = {%u, %u}, curs = {%u, %u}, screen_width = %u\n",
			g_term.curs.x, g_term.curs.y, cmd->curs.x, cmd->curs.y, g_term.w);
	lt_move_cursor(g_term.curs.x, g_term.curs.y);
}

void	copy_and_display_input(t_cmds *cmd, const char buf[], uint32_t len)
{
	unsigned int	i;
	unsigned int	clen;

	dprintf(debug, "buffer[] = \"%.*s\"\n", len, buf);
	i = 0;
	while (i < len)
	{
		clen = get_utf8_char_size(buf + i);
		dprintf(debug, "buf + i = \"%.*s\"\n", clen, buf + i);
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
		dprintf(debug, "buf = \"%.*s\"\n", (int)len, buf);

		if (cmd->pasted)
		{
			lt_move_cursor(cmd->pasted_pos, g_term.curs.y);
			lt_clear_end_of_line();
			// clear x lines, depends of length
			write(STDOUT_FILENO,
					cmd->line[cmd->curs.y] + cmd->pasted_byte,
					cmd->len[cmd->curs.y] - cmd->pasted_byte);
			g_term.curs.x = get_utf8_string_width2(
						cmd->line[cmd->curs.y] + cmd->pasted_byte,
						cmd->len[cmd->curs.y] - cmd->pasted_byte);
			cmd->pasted = 0;
		}

		if (len == 1 && buf[0] == '\n')
		{
			// check quotes
//			if (cmd->quote)
//				write_char_to_cmd(cmd, "<quote>", 7u);
//			else
				break;
		}
		
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
	//printf(" { window resized }\n");
	lt_get_terminal_size(&g_term);
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
