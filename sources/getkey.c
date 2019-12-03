/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 16:24:03 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/03 18:16:24 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libterm.h"
#include "key_list.h"
#include <signal.h>

// https://zestedesavoir.com/tutoriels/pdf/1733/termcap-et-terminfo.pdf
// https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/

// https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html#SEC7
// https://cirw.in/blog/bracketed-paste   http://www.xfree86.org/current/ctlseqs.html#Bracketed%20Paste%20Mode

void	put_sigwinch(int sig)
{
	printf(" { window resized }\n");
}

void	put_sig(int sig)
{
	printf("SIGNAL IS %d\n", sig);
	lt_terminal_mode(LT_RESTORE);
	exit(0);
}

int		main(void)
{
	char			*cmd;
	char			key[16]; // gros tableau pour les copier/coller ?
	unsigned int	klen;
	unsigned int	tmp;
	unsigned int	i;
	unsigned int	paste_mode;

	if (lt_init() != 1)
	{
		fprintf(stderr, "can't initialise libterm\n");
		return (1);
	}

	paste_mode = 0;

	for (int i = 0; i < 33; i++)
		signal(i, put_sig);

	signal(SIGWINCH, put_sigwinch);


	lt_terminal_mode(LT_NOECHO | LT_NOSIG);
	lt_clear_screen();
	lt_set_color(COLOR_CYAN, LT_NONE, LT_BOLD);


	printf("PRESS A KEY >\n");
	while (1)
	{
__read:
		klen = read(STDIN_FILENO, key, 15);
		i = 0;
	
		while ((key[i] >= ' ' && key[i] <= '~') || key[i] == '\n')
		{
			if (key[i] == '!')
			{
				lt_terminal_mode(LT_RESTORE);
				return (0);
			}
			write(1, key + i, 1);
			i++;
			if (--klen == 0)
				goto __read;
		}

		for (; i < klen; i++)
		{
			char	buf[128];
			int		l;
			unsigned int	n;

			n = (unsigned char)key[i];

			write(1, "<", 1);
			buf[0] = '0';
			l = (n == 0) ? 0 : -1;
			while (n)
			{
				if ((n % 16) > 9)
					buf[++l] = (n % 16) + 55;
				else
					buf[++l] = (n % 16) + '0';
				n /= 16;
			}
			while (l != -1)
			{
				write(1, buf + l, 1);
				l--;
			}
			write(1, ">", 1);
		}
	}


	return (0);
}
