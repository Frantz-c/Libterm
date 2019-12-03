#include "libterm.h"

static void	move_cursor_down(uint32_t *y)
{
	if (*y == g_term.h - 1)
	{
		dprintf(debug, "scroll\n");
		lt_move_col(0);
		lt_scroll_up();
		g_term.curs.y--;
	}
	else
	{
		lt_move_down();
		(*y)++;
	}
}

/*
**	print the command but don't care of
**	the cursor's position after execution
*/
void	print_paste(t_cmds *cmd)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	lsize;
	t_pos		ic;

	ic = g_term.curs;
	if (is_cmd_too_large(cmd))
	{
		lt_clear_screen();
		write(STDOUT_FILENO, "cmd too long", 12);
		lt_terminal_mode(LT_RESTORE);
		exit(1);
	}

	lt_set_video_mode(LT_REVERSE);
	lsize = 0;
	y = cmd->curs.y;
	x = g_term.curs.x;
	if (get_utf8_string_width2(cmd->line[y] + cmd->curs.x, cmd->len[y] - cmd->curs.x) <= g_term.w - x)
	{
		lsize = get_utf8_string_size(cmd->line[y] + cmd->curs.x, g_term.w - x, cmd->len[y] - cmd->curs.x);
		if (y == cmd->pasted_beg.y && y == cmd->paste_end.y)
		{
			write(STDOUT_FILENO, cmd->line[y] + cmd->curs.x, cmd->pasted_end.x - cmd->curs.x);
			lt_reset_color();
			write(STDOUT_FILENO, cmd->line[y] + cmd->paste_end.x, lsize - (cmd->paste_end.x - cmd->curs.x));
		}
		else
			write(STDOUT_FILENO, cmd->line[y] + cmd->curs.x, lsize);
		dprintf(debug, "print : \"%.*s\"\n", lsize, cmd->line[y] + cmd->curs.x);
		// créer une fonction
		if (x == g_term.w - 1)
			move_cursor_down(&ic.y);
		if (lsize + cmd->curs.x == cmd->len[y])
			return ;
	}
	dprintf(debug, "x >= g_term.w\n");
	x = cmd->curs.x + lsize;
	while (1)
	{
		// afficher l'excedent sur les lignes suivantes
		while (x != cmd->len[y])
		{
			// créer une fonction
			move_cursor_down(&ic.y);

			dprintf(debug, "while (%u != %u) : 101  while (x != cmd->len[y])\n", x, cmd->len[y]);
			if ((lsize = get_utf8_string_size(cmd->line[y] + x, g_term.w, cmd->len[y] - x)) == 0)
			{
				dprintf(debug, "BREAK\n");
				break ;
			}
			write(STDOUT_FILENO, cmd->line[y] + x, lsize);
			x += lsize;
		}
		if (++y == cmd->n_row)
			break ;
		if (cmd->pad[y])
			write(STDOUT_FILENO, cmd->prefix[y], cmd->pad[y]); // afficher les messages prefixe ("<quote>, ...")
		lsize = get_utf8_string_size(cmd->line[y], g_term.w - cmd->pad[y], cmd->len[y]);
		write(STDOUT_FILENO, cmd->line[y] + cmd->curs.x, lsize);
	}
}


