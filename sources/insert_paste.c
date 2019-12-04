/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_paste.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/03 14:08:38 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/04 14:01:49 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

void	shift_cmd_next_lines(t_cmds *cmd, t_pos *curs)
{
	cmd->line = nalloc(cmd->line, cmd->n_row, cmd->n_row + 1, sizeof(char*));
	cmd->len = nalloc(cmd->len, cmd->n_row, cmd->n_row + 1, sizeof(uint32_t));
	cmd->real_len = nalloc(cmd->real_len, cmd->n_row, cmd->n_row + 1, sizeof(uint32_t));
	cmd->pad = nalloc(cmd->pad, cmd->n_row, cmd->n_row + 1, sizeof(uint32_t));
	cmd->prefix = nalloc(cmd->prefix, cmd->n_row, cmd->n_row + 1, sizeof(char*));
	cmd->n_row++;
	curs->y++;
	if (curs->y != cmd->n_row - 1)
		memmove(cmd->line + curs->y + 1, cmd->line + curs->y, cmd->n_row - curs->y);
	cmd->real_len[curs->y] = 0;
	cmd->len[curs->y] = 0;
	cmd->pad[curs->y] = 0;
	cmd->prefix[curs->y] = NULL;
	cmd->line[curs->y] = NULL;
}

void	paste(char buf[], uint32_t len, t_cmds *cmd)
{
	uint32_t	i;
	uint8_t		end;
	uint32_t	paste_pos;
	char		*remainder;
	uint32_t	remlen;
	uint32_t	start;
	t_pos		curs;
	uint8_t		new_line;

	new_line = 0;
	end = 0;
	paste_pos = cmd->curs.x;
	cmd->pasted_beg = cmd->curs;
	curs.y = cmd->curs.y;
	curs.x = cmd->curs.x;
	if (cmd->len[curs.y] && curs.x < cmd->len[curs.y])
	{
		remlen = cmd->len[curs.y] - curs.x;
		remainder = malloc(remlen);
		memcpy(remainder, cmd->line[curs.y] + curs.x, remlen);
	}
	else
	{
		remainder = NULL;
		remlen = 0;
	}

//	"\e[200~"
//	"une ligne\ndeux lignes\e[201~"
	// if buf == "\e[200~"
	if (len == 0)
		len = read(STDIN_FILENO, buf, READ_LEN - strlen(PASTE_START));

	while (1)
	{
		start = 0;
		i = 0;
		while (i != len)
		{
			if (buf[i] == '\e')
			{
				if (memcmp(PASTE_END, buf + i, strlen(PASTE_END)) == 0)
				{
					if (i != 0)
					{
						if (new_line)
							shift_cmd_next_lines(cmd, &curs);
						// create a function nalloc_and_copy()
						nalloc_if_needed(cmd, curs.y, i - start);
						if (curs.x < cmd->len[curs.y])
							memmove(cmd->line[curs.y] + curs.x + (i - start),
									cmd->line[curs.y] + curs.x,
									(i - start));
						memcpy(cmd->line[curs.y] + curs.x, buf + start, i - start);
						cmd->len[curs.y] += (i - start);
						curs.x += (i - start);
					}
					end = 1;
					break ;
				}
			}
			else if (buf[i] == '\n')
			{
				if (new_line)
					shift_cmd_next_lines(cmd, &curs);
				nalloc_if_needed(cmd, curs.y, i - start);
				if (curs.x && curs.x < cmd->len[curs.y])
					memmove(cmd->line[curs.y] + curs.x + (i - start),
							cmd->line[curs.y] + curs.x,
							i);
				memcpy(cmd->line[curs.y] + curs.x, buf + start, i - start);
				cmd->len[curs.y] += (i - start);
//				curs.x += (i - start);
				start = i + 1;
				curs.x = 0;
				new_line = 1;
			}
			i++;
		}
		if (end)
			break ;

		if (new_line)
			shift_cmd_next_lines(cmd, &curs);

		// create a function nalloc_and_copy()
		nalloc_if_needed(cmd, curs.y, len - start);
		if (curs.x && curs.x < cmd->len[curs.y])
			memmove(cmd->line[curs.y] + curs.x + (len - start),
					cmd->line[curs.y] + curs.x,
					len - start);
		memcpy(cmd->line[curs.y] + curs.x, buf + start, len - start);
		cmd->len[curs.y] += (len - start);
		curs.x += (len - start);
		len = read(STDIN_FILENO, buf, READ_LEN - strlen(PASTE_START));
		new_line = 0;
	}

	if (remainder)
	{
		nalloc_if_needed(cmd, curs.y, remlen);
		memcpy(cmd->line[curs.y] + curs.x, remainder, remlen);
		cmd->len[curs.y] += remlen;
		free(remainder);
	}

	cmd->pasted = 1;
	cmd->pasted_end = curs;

/*
	// DEBUG::check()
	for (unsigned int a = 0; a < cmd->n_row; a++)
	{
		printf("line %d:%u = \"%.*s\"\n", a, cmd->len[a], (int)cmd->len[a], cmd->line[a]);
	}
	lt_terminal_mode(LT_RESTORE);
	exit(0);
*/
	print_paste(cmd);
	lt_move_cursor(g_term.curs.x, g_term.curs.y);
}
