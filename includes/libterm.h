/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libterm.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 12:52:12 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 14:58:22 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBTERM_H
# define LIBTERM_H

# include <curses.h>
# include <term.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>

struct	s_term
{
	unsigned int	w;
	unsigned int	h;
};

typedef struct s_term	t_term;

# define MOVE_CURSOR			"cm"
# define MOVE_CURSOR_HOME		"ho"
# define MOVE_CURSOR_END		"ll"
# define MOVE_UP				"up"
# define MOVE_N_UP				"UP"
# define MOVE_DOWN				"do"
# define MOVE_N_DOWN			"DO"
# define MOVE_LEFT				"le"
# define MOVE_N_LEFT			"LE"
# define MOVE_RIGHT				"nd"
# define MOVE_N_RIGHT			"RI"
# define CLEAR_SCREEN			"cl"
# define CLEAR_SCREEN_FROM		"cd"
# define CLEAR_LINE_AFTER		"ce"
# define CLEAR_N_CHAR			"ec"
# define INSERT_MODE_ON			"im"
# define INSERT_MODE_OFF		"ei"
# define INSERT_BLANK_CHAR		"ic"
# define INSERT_N_BLANK_CHAR	"IC"

# define LT_NONE				0xffff

# define LT_BOLD				0x1
# define LT_UNDERLINE			0x2
# define LT_BLINK				0x8
# define LT_HALFBRIGHT			0x10
# define LT_INVISIBLE			0x20
# define LT_PROTECTED			0x40
# define LT_REVERSE				0x80


/*
** init.c
*/
int		lt_init(void);
int		lt_noecho_mode(void);
void	lt_get_terminal_size(t_term *term);

/*
** clear.c
*/
void	lt_clear_screen(void);
void	lt_clear_screen_from(void);
void	lt_clear_end_of_line(void);
void	lt_clear_n_char(int n);

/*
** move_right_left.c
*/
void	lt_move_right(void);
void	lt_move_n_right(int n);
void	lt_move_left(void);
void	lt_move_n_left(int n);

/*
** move_up_down.c
*/
void	lt_move_up(void);
void	lt_move_n_up(int n);
void	lt_move_down(void);
void	lt_move_n_down(int n);

/*
** move.c
*/
void	lt_move_cursor(int col, int row);
void	lt_move_cursor_home(void);
void	lt_move_cursor_end(void);


/*
** insert_delete_line.c
*/
void	lt_insert_line_before(void);
void	lt_insert_n_lines_before(int n);
void	lt_delete_current_line(void);
void	lt_delete_n_lines_from(int n);

/*
** insert_delete_char.c
*/
void	lt_insert_mode_on(void);
void	lt_insert_mode_off(void);
void	lt_insert_n_blank_char(int n);
void	lt_insert_blank_char(void);

/*
** if size is 0, function use ft_strlen
*/
void	lt_insert_string_at(const char *s, unsigned int size);


/*
** bracketed_paste_mode.c
*/
void	lt_enable_paste_mode(void);
void	lt_disable_paste_mode(void);

/*
** .c
*/

/*
** .c
*/

/*
** .c
*/

/*
** .c
*/

#endif
