/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 16:24:03 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 14:40:39 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libterm.h"
#include <signal.h>

// https://zestedesavoir.com/tutoriels/pdf/1733/termcap-et-terminfo.pdf
// https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/

// https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html#SEC7
// https://cirw.in/blog/bracketed-paste   http://www.xfree86.org/current/ctlseqs.html#Bracketed%20Paste%20Mode

void	put_sigwinch(int sig)
{
	int		w, h;

	printf(" { window resized }\n", w, h);
}

void	put_sig(int sig)
{
	printf("SIGNAL IS %d\n", sig);
}

int		main(void)
{
	char			*cmd;
	char			key[4]; // gros tableau pour les copier/coller ?
	unsigned int	klen;

	if (lt_init() != 1)
	{
		fprintf(stderr, "can't initialise libterm\n");
		return (1);
	}


	for (int i = 0; i < 33; i++)
		signal(i, put_sig);

	signal(SIGWINCH, put_sigwinch);


	lt_noecho_mode();
	lt_enable_paste_mode();
	lt_clear_screen();
	lt_set_color(COLOR_RED, LT_NONE, LT_NONE);

//	print_prompt("mhfc_42sh$ ");
//	cmd = get_user_command();

	while (1)
	{
		klen = read(STDIN_FILENO, key, 4);

		for (unsigned int i = 0; i < klen; i++)
		{

			if (key[i] >= ' ' && key[i] <= '~')
				write(1, key + i, 1);
			else
			{
				char	buf[128];
				int		l;
				int		sign;

				if (key[i] < 0)
				{
					sign = 1;
					key[i] = (~key[i]) + 1;
				}
				else
					sign = 0;

				write(1, "<", 1);
				buf[0] = '0';
				l = (key[i] == 0) ? 0 : -1;
				while (key[i])
				{
					buf[++l] = ((key[i] % 10) + '0');
					key[i] /= 10;
				}
				if (sign)
					buf[++l] = '-';
				while (l != -1)
				{
					write(1, buf + l, 1);
					l--;
				}
				write(1, ">", 1);
			}
			if (key[i] == '&')
			{
				lt_noecho_mode();
				return (0);
			}
		}
	}


	return (0);
}
