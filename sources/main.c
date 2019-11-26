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
}

typedef struct	keyname_s
{
	char	*value;
	char	*name;
}
keyname_t;

keyname_t	button[] = {
	{F1, "<F1>"}, {F2, "<F2>"}, {F3, "<F3>"}, {F4, "<F4>"},
	{F5, "<F5>"}, {F6, "<F6>"}, {F7, "<F7>"}, {F8, "<F8>"},
	{F9, "<F9>"}, {F10, "<F10>"}, {F12, "<F12>"},
	{L_ARROW, "<LEFT>"}, {R_ARROW, "<RIGHT>"}, {U_ARROW, "<UP>"}, {D_ARROW, "<DOWN>"},
	{CTRL_A, "<C^A>"}, {CTRL_B, "<C^B>"}, {CTRL_C, "<C^C>"}, {CTRL_D, "<C^D>"},
	{CTRL_E, "<C^E>"}, {CTRL_F, "<C^F>"}, {CTRL_G, "<C^G>"}, {CTRL_H, "<C^H>"},
	{CTRL_I, "<C^I/M>"}, /*{CTRL_J, "<C^J>"}, */{CTRL_K, "<C^K>"}, {CTRL_L, "<C^L>"},
	{CTRL_N, "<C^N>"}, {CTRL_O, "<C^O>"}, {CTRL_P, "<C^P>"}, {CTRL_R, "<C^R>"},
	{CTRL_T, "<C^T>"}, {CTRL_U, "<C^U>"}, {CTRL_V, "<C^V>"}, {CTRL_W, "<C^W>"},
	{CTRL_X, "<C^X>"}, {CTRL_Y, "<C^Y>"}, {CTRL_Z, "<C^Z>"},
	{ALT_A, "<ALT-A>"}, {ALT_B, "<ALT-B>"}, {ALT_C, "<ALT-C>"}, {ALT_D, "<ALT-D>"},
	{ALT_E, "<ALT-E>"}, {ALT_F, "<ALT-F>"}, {ALT_G, "<ALT-G>"}, {ALT_H, "<ALT-H>"},
	{ALT_I, "<ALT-I>"}, {ALT_J, "<ALT-J>"}, {ALT_K, "<ALT-K>"}, {ALT_L, "<ALT-L>"},
	{ALT_M, "<ALT-M>"}, {ALT_N, "<ALT-N>"}, {ALT_O, "<ALT-O>"}, {ALT_P, "<ALT-P>"},
	{ALT_Q, "<ALT-Q>"}, {ALT_R, "<ALT-R>"}, {ALT_S, "<ALT-S>"}, {ALT_T, "<ALT-T>"},
	{ALT_U, "<ALT-U>"}, {ALT_V, "<ALT-V>"}, {ALT_W, "<ALT-W>"}, {ALT_X, "<ALT-X>"},
	{ALT_Z, "<ALT-Z>"}, {ESCAPE, "<ESC>"}, {LINEFEED, "\n"}, {PASTE_START, "<PASTE>"},
	{NULL, NULL}
};

int		get_key(const char *k, unsigned int *index)
{
	for (unsigned int i = 0; button[i].name; i++)
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

int		main(void)
{
	char			*cmd;
	char			key[16]; // gros tableau pour les copier/coller ?
	unsigned int	klen;
	unsigned int	tmp;

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
	lt_set_color(COLOR_RED, COLOR_WHITE, LT_UNDERLINE | LT_BOLD);

//	print_prompt("mhfc_42sh$ ");
//	cmd = get_user_command();

	while (1)
	{
		klen = read(STDIN_FILENO, key, 9);
		key[klen] = 0;

		if (get_key(key, &tmp))
			continue ;

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
