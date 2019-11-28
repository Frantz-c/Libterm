/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libterm.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 12:52:12 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 19:44:49 by fcordon     ###    #+. /#+    ###.fr     */
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
# include <stdint.h>
# include "macro.h"
# include "key_list.h"
# include "structures.h"

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
# define LT_BLINK				0x4
# define LT_HALFBRIGHT			0x8
# define LT_INVISIBLE			0x10
# define LT_PROTECTED			0x20
# define LT_REVERSE				0x40
# define LT_MODE_END			0x80


extern t_term				g_term;

/*
** init.c
*/
int		lt_init(void);
int		lt_terminal_mode(uint32_t mode);
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
** display_attributes.c
*/
void	lt_set_color(int color1, int color2, int video_mode);
void	lt_reset_color(void);
void	lt_set_fg_color(int color);
void	lt_set_bg_color(int color);
void	lt_set_video_mode(int mode);


/*
** utf8.c
*/
uint8_t		secure_get_utf8_char_size(const char *str, uint32_t len);
uint8_t		get_utf8_char_width(const char *s);
uint8_t		get_utf8_char_size(const char *s);
uint32_t	strlen_utf8(const char *s);
uint32_t	get_utf8_string_width(const char *s);
uint32_t	get_utf8_string_width2(const char *s, uint32_t bytes);
uint8_t		get_utf8_prev_char_width(const char *s);
uint8_t		get_utf8_prev_char_size(const char *s);
void		get_utf8_prev_char_info(const char *s, uint8_t *width, uint8_t *size);
void		get_utf8_char_info(const char *s, uint8_t *width, uint8_t *size);


/*
** escape_action.c
*/
void	l_arrow(t_cmds *cmd);
void	u_arrow(t_cmds *cmd);
void	d_arrow(t_cmds *cmd);
void	r_arrow(t_cmds *cmd);
void	maj_right(t_cmds *cmd);
void	maj_left(t_cmds *cmd);
void	delete(t_cmds *cmd);
void	escape(t_cmds *cmd);
void	f1(t_cmds *cmd);
void	f2(t_cmds *cmd);
void	f3(t_cmds *cmd);
void	f4(t_cmds *cmd);
void	f5(t_cmds *cmd);
void	f6(t_cmds *cmd);
void	f7(t_cmds *cmd);
void	f8(t_cmds *cmd);
void	f9(t_cmds *cmd);
void	f10(t_cmds *cmd);
void	f12(t_cmds *cmd);

/*
** control_action.c
*/
void	ctrl_a(t_cmds *cmd);
void	ctrl_b(t_cmds *cmd);
void	ctrl_c(t_cmds *cmd);
void	ctrl_d(t_cmds *cmd);
void	ctrl_e(t_cmds *cmd);
void	ctrl_f(t_cmds *cmd);
void	ctrl_g(t_cmds *cmd);
void	ctrl_h(t_cmds *cmd);
void	ctrl_i(t_cmds *cmd);
void	ctrl_k(t_cmds *cmd);
void	ctrl_l(t_cmds *cmd);
void	ctrl_n(t_cmds *cmd);
void	ctrl_o(t_cmds *cmd);
void	ctrl_p(t_cmds *cmd);
void	ctrl_r(t_cmds *cmd);
void	ctrl_t(t_cmds *cmd);
void	ctrl_u(t_cmds *cmd);
void	ctrl_v(t_cmds *cmd);
void	ctrl_w(t_cmds *cmd);
void	ctrl_x(t_cmds *cmd);
void	ctrl_y(t_cmds *cmd);
void	ctrl_z(t_cmds *cmd);

/*
**	print_prompt.c
*/
uint32_t	print_prompt(const char *prompt, uint32_t len);

/*
**	execute_special_keys.c
*/
uint32_t	execute_escape_sequence(t_cmds *cmd, char *buf, uint32_t *len);
void	execute_control(t_cmds *cmd, char c);

/*
**	backspace.c
*/
void	backspace(t_cmds *cmd);

#endif
