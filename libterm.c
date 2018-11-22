/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   terminal.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/11 10:29:14 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 18:08:36 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"
#include <termios.h>
#include <unistd.h>
#include <dirent.h>
#include "libft/libft.h"


/*
** STATIC FUNCTIONS
*/

static int		ft_streqlen(char *s1, char *s2)
{
	int ret = 0;

	while (*s1 && (*(s1++) == *(s2++)))	ret++;
	return (ret);
}

static int		ft_contained(char *s1, char *s2)
{
	while (*s2 && *s1 == *s2)
		s1++, s2++;
	return (*s2 == 0) ? 1 : 0;
}

static int		autocomplete_list(char *buf, int size)
{
	DIR				*dir;
	struct dirent	*d;
	char			*slash_pos;
	int				eql = 0x7fffffff;
	int				n_path = 0;
	char			**menu = NULL;

	if ((slash_pos = ft_strrchr(buf, '/')) == NULL)
		return (0);
	slash_pos++;
	if ((dir = opendir(buf)) == NULL)
		return (0);

	menu = malloc(sizeof(char*) * 200); // warning
	while ((d = readdir(dir)) != NULL)
	{
		if (*d->d_name == '.')	continue ;
		menu[n_path++] = ft_strjoin(d->d_name, "\r\n");
	}
	menu[n_path] = NULL;

	store_cursor();
	hide_cursor();
	write(1, "\n", 1);
	n_path = display_menu_list((const char **)menu, n_path, RED1, WHIT0);
	eql = ft_strlen(menu[n_path]) - 2;
	if (eql >= size - (slash_pos - buf))
		goto ret_0;
	ft_strncpy(slash_pos, menu[n_path], eql);
	ft_free2d(menu);
	display_cursor();
	load_cursor();

	closedir(dir);
	return (1);

ret_0:
	closedir(dir);
	return (0);
}

static int		autocomplete(char *buf, int size, int path_list)
{
	DIR				*dir;
	struct dirent	*d;
	char			path[200] = {0};
	char			*slash_pos;
	char			*candidat = NULL;
	int				eql = 0x7fffffff;
	int				new_eql = 0;
	int				mult_cand = 0;
	int				search_len;
	int				n_path = 0;
	char			**menu = NULL;

	if ((slash_pos = ft_strrchr(buf, '/')) == NULL)
		return (0);
	slash_pos++;
	ft_strncpy(path, buf, (slash_pos) - buf);
	if ((dir = opendir(path)) == NULL)
		return (0);

	if (path_list)
		menu = malloc(sizeof(char*) * 50); // warning
	search_len = ft_strlen(slash_pos);
	while ((d = readdir(dir)) != NULL)
	{
		if (*d->d_name == '.')	continue ;
		if (!candidat)
		{
			if (ft_contained(d->d_name, slash_pos)) {
				candidat = d->d_name;
				if (path_list)
					menu[n_path++] = ft_strjoin(d->d_name, "\r\n");
			}
		}
		else if (ft_contained(d->d_name, slash_pos))
		{
			if ((new_eql = ft_streqlen(candidat, d->d_name)) < eql) {
				mult_cand++;
				eql = new_eql;
			}
			if (path_list)
				menu[n_path++] = ft_strjoin(d->d_name, "\r\n");
		}
	}
	if (path_list)
		menu[n_path] = NULL;

	if (mult_cand && path_list)
	{
		store_cursor();
		hide_cursor();
		write(1, "\n", 1);
		n_path = display_menu_list((const char **)menu, n_path, RED1, WHIT0);
		eql = ft_strlen(menu[n_path]) - 2;
		if (eql >= size - (slash_pos - buf))
			goto ret_0;
		ft_strncpy(slash_pos, menu[n_path], eql);
		load_cursor();
		display_cursor();
		goto ret_1;
	}


	if (!candidat)				goto ret_0;
	if (!mult_cand)
	{
		eql = ft_strlen(candidat);
		if (eql >= size - (slash_pos - buf))
			goto ret_0;
		ft_strncpy(slash_pos, candidat, eql);
	}
	else if (eql <= search_len)	goto ret_0;
	else
	{
		if (eql >= size - (slash_pos - buf))
			goto ret_0;
		ft_strncpy(slash_pos, candidat, eql);
	}

ret_1:
	if (path_list)
		ft_free2d(menu);
	closedir(dir);
	return (1);

ret_0:
	if (path_list)
		ft_free2d(menu);
	closedir(dir);
	return (0);
}

/*
 ** TERMINAL MODES
 */

extern void		make_terminal_raw(int mode)
{
	static struct termios	cooked; 
	static int				rawmode = 0; 
	static int				first = 1; 
	struct termios			raw; 

	if (rawmode == mode)
		return ;
	if (first)
	{
		first = 0;
		tcgetattr(0, &cooked);
	}
	if ((rawmode = mode) == 1)
	{
		raw = cooked; 
		cfmakeraw(&raw); 
		tcsetattr(0, TCSANOW, &raw); 
		return ;
	}
	tcsetattr(0, TCSANOW, &cooked); 
}




/*
 ** STD INPUT FUNCTIONS
 */

extern t_key	get_key(void)
{
	char	 c;

	make_terminal_raw(1);
	read(0, &c, 1);
	if (c == 27)
	{
		read(0, &c, 1);
		if (c == 91)
		{
			read(0, &c, 1);
			if		(c > 64 && c < 69)	return(c + 63);
			else if (c == 51)			return(KEY_DEL);
			else if (c == 49)			return(KEY_F5_8);
			else if (c == 50)			return(KEY_F9_12);
		}
		else if (c == 79)
		{
			read(0, &c, 1);
			if (c > 79 && c < 84)		return(c + 53);
		}
	}
	make_terminal_raw(0);
	return (c);
}

extern void		get_user_input(char *buf, long size)
{
	size--;
	if (read(0, buf, size) != size)
		ft_memcrrep(buf, '\n', '\0', size);
	else
		buf[size] = '\0';
}

extern void	advanced_user_input(char *buf, int size, int flag)
{
	t_key	key;
	int		len = ft_strlen(buf);
	int		curs = len;
	int		tmpl;

	ft_puts(buf);
	make_terminal_raw(1);

	while ((key = get_key()) != KEY_ENTER)
	{
		if (key == KEY_BACKSP && len)
		{
			move_cursor_left();
			if (curs == len) {
				buf[len - 1] = '\0';
				ft_putc(KEY_SPACE);
				move_cursor_left();
			}
			else {
				tmpl = ft_strlen(buf + (curs)) + 1;
				ft_memmove(buf + (curs - 1), buf + (curs), tmpl);
				erase_line_end();
				ft_puts(buf + (curs - 1));
				move_cursor(KEY_LEFT, tmpl - 1);
			}
			len--;
			curs--;
		}
		else if (key == KEY_LEFT && curs)
		{
			move_cursor_left();
			curs--;
		}
		else if (key == KEY_RIGHT && curs < len)
		{
			move_cursor_right();
			curs++;
		}
		else if (curs >= size - 1 || len >= size -1)
		{
			continue;
		}
		else if (key >= KEY_SPACE && key <= KEY_TILD)
		{
			if (curs == len) {
				buf[len] = key;
				write(1, &key, 1);
			}
			else {
				tmpl = ft_strlen(buf + curs);
				ft_memmove(buf + curs + 1, buf + curs, tmpl);
				buf[curs] = key;
				ft_puts(buf + curs);
				move_cursor(KEY_LEFT, tmpl);
			}
			curs++;
			len++;
		}
		else if (key == KEY_TAB && flag & PATH_AUTOCOMP)
		{
			if ( (buf[len - 1] != '/' && autocomplete(buf, size - 1, flag & PATH_LIST))
					|| (buf[len - 1] == '/' && flag & PATH_LIST && autocomplete_list(buf, size - 1)))
			{
				ft_puts(buf + curs);
				curs = ft_strlen(buf);
				len = curs;
			}
		}
	}
	buf[len] = '\0';
	make_terminal_raw(0);
}




/*
 **	MENU DISPLAY FUNCTIONS
 */
extern void		display_menu_lcm(const char **list, int size, t_menu *opt, int *t)
{
	int		selected = 0;
	t_key	c;
	int		i;

	size--;
	make_terminal_raw(1);

	while (1)
	{
		/*
		 ** print menu with current choice and selected choices highlighting
		 */
		i = 0;
		ft_puts(opt->others);
		while (list[i])
		{
			erase_line_end();
			if (i == selected)
			{
				ft_puts(opt->select);
				ft_puts(list[i]);
				ft_puts(opt->others);
			}
			else if (t[i] == 1)
			{
				ft_puts(opt->action);
				ft_puts(list[i]);
				ft_puts(opt->others);
			}
			else
				ft_puts(list[i]);
			i++;
		}


		/*
		 **	get pressed key & execute action
		 */
		c = get_key();
		if		(c == KEY_ENTER) {
			if (selected == size) break ;
			t[selected] = (t[selected] == 0) ? 1 : 0;
		}
		else if (c == KEY_BACKSP)	break ;
		else if (c == KEY_UP)		selected = (selected == 0) ? size : selected - 1;
		else if (c == KEY_DOWN)		selected = (selected == size) ? 0: selected + 1;
		move_cursor(KEY_UP, size + 1);
	}
	size++;
	clear_line_and_move_up(size);
	make_terminal_raw(0);
}

extern int		display_menu_list(const char **list, int size, const char *s_color, const char *o_color)
{
	int			selected = 0;
	t_key		c;
	int			i;
	int			list_x, list_y;
	int			x_print;
	int			y_print;
	int			list_h;

	get_cursor_position(&list_x, &list_y);
	list_h = terminal_h - list_y;
	make_terminal_raw(1);
	while (1)
	{
		x_print = list_x;
		/*
		** print menu with current choice highlighting
		*/
		i = 0;
		ft_puts(o_color);
		while (list[i])
		{
			y_print = (i != 0) ? list_y + ((i + 1) % list_h) : list_y;
			if (((i + 1) % list_h) == 0)
				x_print += 40;

			if (i == selected)
			{
				ft_puts(s_color);
				xyprint(list[i], x_print, y_print);
				ft_puts(o_color);
			}
			else
				xyprint(list[i], x_print, y_print);
			i++;
		}

		/*
		 **	get pressed key & action
		 */
		c = get_key();
		if		(c == KEY_ENTER)	break ;
		else if (c == KEY_UP)		selected = (selected == 0) ? size - 1: selected - 1;
		else if (c == KEY_DOWN)		selected = (selected == size - 1) ? 0: selected + 1;
		else if (c == KEY_LEFT)		selected = (selected > list_h) ? selected - list_h: (selected % (size % list_h)) + (size - (size % list_h));
		else if (c == KEY_RIGHT)	selected = (selected < size - list_h) ? selected + list_h: selected % list_h;
		//move_cursor_xy(list_x, list_y);
	}
	move_cursor_xy(list_x, list_y + list_h);
	clear_line_and_move_up2(list_h + 1);
	make_terminal_raw(0);
	return (selected);
}



/*
 ** PRINT FUNCTIONS
 */

extern void		xyprint(const char *s, int x, int y)
{
	const size_t	length = ft_strnlen(s, terminal_w - x);

	//store_cursor();
	move_cursor_xy(x, y);
	write(1, s, length);
	//load_cursor();
}

extern void		xyprint_color(const char *s, int x, int y, const char *color)
{
	const size_t	length = ft_strnlen(s, terminal_w - x);

	//store_cursor();
	move_cursor_xy(x, y);
	ft_puts(color);
	write(1, s, length);
	write(1, "\e[0m", 4);
	//write(1, "\e[0m\e8", 6);
}

extern void		print_animation(char **img, unsigned int n_lines, unsigned int interval)
{
	while (1)
	{
		ft_puts(*img);
		usleep(interval);
		clear_line_and_move_up2(n_lines);
		if (*(++img) == NULL)
			break ;
	}
}




/*
 **	TERMINAL SIZE
 */

extern void		get_terminal_size(int *intx, int *inty)
{
	char	*x;
	char	*y;
	int		i;
	char	buf[11];

	store_cursor();
	make_terminal_raw(1);
	write(1, "\e[999;999H\e[6n", 14);
	i = read(0, buf, 10);
	make_terminal_raw(0);
	buf[i] = 0;
	y = buf + 2;
	i -= 2;
	buf[i + 1] = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
		i--;
	x = buf + i + 1;
	*intx = ft_atoi(x);
	*inty = ft_atoi(y);
	load_cursor();
}




/*
 ** CURSOR FUNCTIONS
 */
extern void		get_cursor_position(int *intx, int *inty)
{
	char	*x;
	char	*y;
	int		i;
	char	buf[11];

	make_terminal_raw(1);
	write(1, "\e[6n", 4);
	i = read(0, buf, 10);
	make_terminal_raw(0);
	buf[i] = 0;
	y = buf + 2;
	i -= 2;
	buf[i + 1] = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
		i--;
	x = buf + i + 1;
	*intx = ft_atoi(x);
	*inty = ft_atoi(y);
}

extern void		move_cursor(unsigned int flag, unsigned int n)
{
	char	buf[24];
	int		i;
	int		length;

	length = 3;
	buf[23] = 0;
	if		(flag == KEY_UP)	buf[22] = 'A';
	else if (flag == KEY_DOWN)	buf[22] = 'B';
	else if (flag == KEY_LEFT)	buf[22] = 'D';
	else if (flag == KEY_RIGHT)	buf[22] = 'C';
	i = 21;
	while (n)
	{
		buf[i--] = (n % 10) + 48;
		n /= 10;
		length++;
	}
	buf[i--] = '[';
	buf[i] = '\e';
	write(1, buf + i, length);
}

extern void		move_cursor_xy(unsigned int x, unsigned int y)
{
	char	buf[23];
	int		i;
	int		length;

	length = 4;
	buf[22] = 'H';
	i = 21;
	while (x)
	{
		buf[i--] = (x % 10) + 48;
		x /= 10;
		length++;
	}
	buf[i--] = ';';
	while (y)
	{
		buf[i--] = (y % 10) + 48;
		y /= 10;
		length++;
	}
	buf[i--] = '[';
	buf[i] = '\e';
	write(1, buf + i, length);
}
