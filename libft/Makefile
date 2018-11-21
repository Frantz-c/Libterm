PATH = ./
NAME = libft.a
CC = gcc -Wall -Werror -Wextra -O3 
FILES = ft_atoi.o\
ft_free2d.o\
ft_atol.o\
ft_bzero.o\
ft_crep.o\
ft_crepall.o\
ft_crrep.o\
ft_free_options.o\
ft_get_opt_value.o\
ft_get_options.o\
ft_getline.o\
ft_getline_mfd.o\
ft_isalnum.o\
ft_isalpha.o\
ft_isascii.o\
ft_isdigit.o\
ft_isprint.o\
ft_isset_option.o\
ft_isspace.o\
ft_itoa.o\
ft_ltoa.o\
ft_ltrim.o\
ft_memalloc.o\
ft_memccpy.o\
ft_memchr.o\
ft_memcmp.o\
ft_memcpy.o\
ft_memcrep.o\
ft_memcrepall.o\
ft_memcrrep.o\
ft_memdel.o\
ft_memdup.o\
ft_memmove.o\
ft_mempcpy.o\
ft_memrchr.o\
ft_memrcpy.o\
ft_memset.o\
ft_print_options.o\
ft_putbin.o\
ft_putc.o\
ft_putchar_fd.o\
ft_putendl.o\
ft_putendl_fd.o\
ft_puts.o\
ft_putstr_fd.o\
ft_sort.o\
ft_strcat.o\
ft_strchr.o\
ft_strclr.o\
ft_strcmp.o\
ft_strcpy.o\
ft_strctrim.o\
ft_strdup.o\
ft_strfcat.o\
ft_strjoin.o\
ft_strlcat.o\
ft_strlen.o\
ft_strncat.o\
ft_strncmp.o\
ft_strncpy.o\
ft_strndup.o\
ft_strnfcat.o\
ft_strnlen.o\
ft_strnstr.o\
ft_strrchr.o\
ft_strrep.o\
ft_strsplit.o\
ft_strstr.o\
ft_strsub.o\
ft_strtolower.o\
ft_strtoupper.o\
ft_strtrim.o\
ft_swap.o\
ft_tolower.o\
ft_toupper.o

all: $(NAME)

$(NAME): $(PATH)$(FILES)
	@ar rc $@ $^ 
	@ranlib $@

.c.o:
	@$(CC) -c $<

clean:
	@/bin/rm -f $(PATH)$(FILES)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

allc: all clean
