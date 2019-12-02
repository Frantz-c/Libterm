#include "libterm.h"

void	lt_get_cursor_position(uint32_t *x, uint32_t *y)
{
	char	buf[8];

	*x = 0u;
	*y = 0u;
	write(STDERR_FILENO, "\e[6n", 4);
	while (read(STDIN_FILENO, buf, 2) && *buf != '\e');
	while (read(STDIN_FILENO, buf, 1) && *buf != ';')
		*y = (*y * 10) + (*buf - '0');
	while (read(STDIN_FILENO, buf, 1) && *buf != 'R')
		*x = (*x * 10) + (*buf - '0');
	(*y)--;
	(*x)--;
}
