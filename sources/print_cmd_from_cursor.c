#include "libterm.h"

static void	move_cursor_down(uint32_t *y, int line)
{
	dprintf(debug, "call move_cursor_down(%u) : line %d\n", *y, line);
	if (*y == g_term.h - 1)
	{
		dprintf(debug, "scroll\n");
		lt_move_col(0);
		lt_scroll_up();
		g_term.curs.y--;
	}
	else
		(*y)++;
}

//prompt$ "un texte de test"|

/*
**	print the command but don't care of
**	the cursor's position after execution
*/
void	print_cmd_from_cursor2(t_cmds *cmd)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	lsize;
	t_pos		ic;

	ic = g_term.curs;
	if (is_cmd_bigger_than_screen(cmd) == LT_TRUE)
	{
		lt_clear_screen();
		write(STDOUT_FILENO, "cmd too long", 12);
		lt_terminal_mode(LT_RESTORE);
		exit(1);
	}

	lsize = 0;
	y = cmd->curs.y;

	/*
	**	print the first line
	*/
	lsize = get_utf8_string_size(cmd->line[y] + cmd->curs.x, g_term.w - g_term.curs.x, cmd->len[y] - cmd->curs.x);
	dprintf(debug, "(1)print: \"%.*s\"\n", lsize, cmd->line[y] + cmd->curs.x);
	write(STDOUT_FILENO, cmd->line[y] + cmd->curs.x, lsize);

	// move cursor down when writting last character of the line
	if (g_term.curs.x == (g_term.w - 1) && (lsize + cmd->curs.x) == cmd->len[y])
		move_cursor_down(&ic.y, __LINE__);
	if ((x = (lsize + cmd->curs.x)) == cmd->len[y] && y == cmd->n_row - 1)
		return ;

	dprintf(debug, "x = %u, cmd->len[y] = %u\n", x, cmd->len[y]);
	/*
	**	print the reminder of the line and the other lines
	*/
	while (1)
	{
		while (x != cmd->len[y])
		{
			move_cursor_down(&ic.y, __LINE__);

			if ((lsize = get_utf8_string_size(cmd->line[y] + x, g_term.w, cmd->len[y] - x)) == 0)
			{
				dprintf(debug, "BREAK\n");
				break ;
			}
			dprintf(debug, "(2)print: \"%.*s\"\n", lsize, cmd->line[y] + x);
			write(STDOUT_FILENO, cmd->line[y] + x, lsize);
			x += lsize;
			dprintf(debug, "x = %u, cmd->len[y] = %u\n", x, cmd->len[y]);
		}
		if (++y == cmd->n_row)
			break ;
		if (cmd->pad[y])
			write(STDOUT_FILENO, cmd->prefix[y], cmd->pad[y]); // afficher les messages prefixe ("<quote>, ...")
		lsize = get_utf8_string_size(cmd->line[y], g_term.w - cmd->pad[y], cmd->len[y]);
		write(STDOUT_FILENO, cmd->line[y], lsize);
	}
}
