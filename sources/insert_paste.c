
void	paste(char buf[], uint32_t len, t_cmds *cmd)
{
	uint32_t	i;
	uint8_t		end;
	uint32_t	paste_pos;

	end = 0;
	paste_pos = cmd->curs.x;
	cmd->pasted_pos = cmd->curs.x;
//	cmd->pasted_pos = g_term.curs.x;
	cmd->pasted_len = 0;

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
						// create a function nalloc_and_copy()
						nalloc_if_needed(cmd, i);
						if (cmd->curs.x == cmd->len[cmd->curs.y])
							memmove(cmd->line[cmd->curs.y] + cmd->curs.x + i,
									cmd->line[cmd->curs.y] + cmd->curs.x,
									i);
						memcpy(cmd->line[cmd->curs.y] + cmd->curs.x, buf, i);
						cmd->len[cmd->curs.y] += i;
						cmd->curs.x += i;
						cmd->pasted_len += i;
					}
					end = 1;
					break ;
				}
			}
			i--;
		}
		if (end)
			break ;
		// create a function nalloc_and_copy()
		nalloc_if_needed(cmd, len);
		if (cmd->curs.x == cmd->len[cmd->curs.y])
			memmove(cmd->line[cmd->curs.y] + cmd->curs.x + i,
					cmd->line[cmd->curs.y] + cmd->curs.x,
					i);
		memcpy(cmd->line[cmd->curs.y] + cmd->curs.x, buf, len);
		cmd->len[cmd->curs.y] += len;
		cmd->curs.x += len;
		cmd->pasted_len += len;
		len = read(STDIN_FILENO, buf, READ_LEN - strlen(PASTE_START));
	}
	cmd->pasted = 1;
}
