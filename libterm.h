/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   terminal.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/11 22:19:14 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 20:47:29 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

int				terminal_w;
int				terminal_h;


/*
**	MACRO
*/
#define erase_line()						write(1, "\e[2K", 4)
#define erase_line_end()					write(1, "\e[K", 3)
#define erase_line_start()					write(1, "\e[1K", 4)
#define terminal_init()						get_terminal_size(&terminal_w, &terminal_h)
#define clear_screen_below()				write(1, "\e[j", 3)
#define clear_screen_above()				write(1, "\e[1J", 4)
#define clear_screen()						write(1, "\e[2J", 4)
#define display_cursor()					write(1, "\e[?25h", 6)
#define store_cursor()						write(1, "\e7", 2)
#define load_cursor()						write(1, "\e8", 2)
#define move_cursor_home()					write(1, "\e[H", 3)
#define clear_and_home()					write(1, "\e[H\e[2J", 7)
#define invert_colors()						write(1, "\e[?5h", 5)
#define restore_colors()					write(1, "\e[?5l", 5)
#define hide_cursor()						write(1, "\e[?25l", 6)
#define move_cursor_left()					write(1, "\e[1D", 4)
#define move_cursor_right()					write(1, "\e[1C", 4)
#define clear_line_and_move_up(n_lines)		int zzz = n_lines; while (zzz--) write(1, "\e[2K\e[A", 7);
#define clear_line_and_move_up2(n_lines)	int zzz = n_lines; while (zzz--) write(1, "\e[K\e[A", 6);
#define clear_line_and_move_down(n_lines)	int zzz = n_lines; while (zzz--) write(1, "\e[K\e[B", 6);

#define PATH_AUTOCOMP	1

#define KEY_UP			128U
#define KEY_DOWN		129U
#define KEY_LEFT		131U
#define KEY_RIGHT		130U
#define KEY_ENTER		13U
#define KEY_DEL			132U
#define KEY_BACKSP		127U
#define KEY_ESC			27U
#define KEY_TAB			9U
#define KEY_TILD		126U
#define KEY_SPACE		32U

#define KEY_A	65U
#define KEY_B	66U
#define KEY_C	67U
#define KEY_D	68U
#define KEY_E	69U
#define KEY_F	70U
#define KEY_G	71U
#define KEY_H	72U
#define KEY_I	73U
#define KEY_J	74U
#define KEY_K	75U
#define KEY_L	76U
#define KEY_M	77U
#define KEY_N	78U
#define KEY_O	79U
#define KEY_P	80U
#define KEY_Q	81U
#define KEY_R	82U
#define KEY_S	83U
#define KEY_T	84U
#define KEY_U	85U
#define KEY_V	86U
#define KEY_W	87U
#define KEY_X	88U
#define KEY_Y	89U
#define KEY_Z	90U

#define KEY_a	97U
#define KEY_b	98U
#define KEY_c	99U
#define KEY_d	100U
#define KEY_e	101U
#define KEY_f	102U
#define KEY_g	103U
#define KEY_h	104U
#define KEY_i	105U
#define KEY_j	106U
#define KEY_k	107U
#define KEY_l	108U
#define KEY_m	109U
#define KEY_n	110U
#define KEY_o	111U
#define KEY_p	112U
#define KEY_q	113U
#define KEY_r	114U
#define KEY_s	115U
#define KEY_t	116U
#define KEY_u	117U
#define KEY_v	118U
#define KEY_w	119U
#define KEY_x	120U
#define KEY_y	121U
#define KEY_z	122U

#define KEY_0	48U
#define KEY_1	49U
#define KEY_2	50U
#define KEY_3	51U
#define KEY_4	52U
#define KEY_5	53U
#define KEY_6	54U
#define KEY_7	55U
#define KEY_8	56U
#define KEY_9	57U

#define CTRL_A	1U
#define CTRL_B	2U
#define CTRL_C	3U
#define CTRL_D	4U
#define CTRL_E	5U
#define CTRL_F	6U
#define CTRL_G	7U
#define CTRL_H	8U
#define CTRL_I	9U
#define CTRL_J	10U
#define CTRL_K	11U
#define CTRL_L	12U
#define CTRL_M	13U
#define CTRL_N	14U
#define CTRL_O	15U
#define CTRL_P	16U
#define CTRL_Q	17U
#define CTRL_R	18U
#define CTRL_S	19U
#define CTRL_T	20U
#define CTRL_U	21U
#define CTRL_V	22U
#define CTRL_W	23U
#define CTRL_X	24U
#define CTRL_Y	25U
#define CTRL_Z	26U

#define KEY_F1		133U
#define KEY_F2		134U
#define KEY_F3		135U
#define KEY_F4		136U
#define KEY_F5_8	137U
#define KEY_F9_12	138U

#define BLAC0	"\e[0;30m"
#define RED0	"\e[0;31m"
#define GREE0	"\e[0;32m"
#define YELL0	"\e[0;33m"
#define BLUE0	"\e[0;34m"
#define PURP0	"\e[0;35m"
#define TURQ0	"\e[0;36m"
#define WHIT0	"\e[0;37m"
#define BLAC1	"\e[1;30m"
#define RED1	"\e[1;31m"
#define GREE1	"\e[1;32m"
#define YELL1	"\e[1;33m"
#define BLUE1	"\e[1;34m"
#define PURP1	"\e[1;35m"
#define TURQ1	"\e[1;36m"
#define WHIT1	"\e[1;37m"
#define NOCOL	"\e[0m"
#define BELOW	0
#define ABOVE	1
#define ALL		2

typedef unsigned int	t_key;

typedef struct		s_menu
{
	char *select;
	char *others;
	char *action;
}					t_menu;

void	make_terminal_raw(int mode);
t_key	get_key(void);
void	move_cursor(unsigned int flag, unsigned int n);
void	move_cursor_xy(unsigned int x, unsigned int y);
void	print_animation(char **img, unsigned int n_lines,
						unsigned int interval);
void	get_terminal_size(int *intx, int *inty);
void	get_cursor_position(int *intx, int *inty);
void	get_user_input(char *buf, long size);
void	advanced_user_input(char *buf, int size, int flag);
void	xyprint(const char *s, int x, int y);
void	xyprint_color(const char *s, int x, int y, const char *color);
void	display_menu_lcm(const char **list, int size, t_menu *opt, int *t);
int		display_menu_list(const char **list, int size,
							const char *s_color, const char *o_color);

#endif
