NAME = libterm.a
CC = gcc -Wall -O3
FILES = libterm.o

all: $(NAME)

$(NAME): $(FILES)
	@make -C libft
	@ar rc $@ $^ libft/libft.a
	@ranlib $@

.c.o:
	@$(CC) -c $<

clean:
	@/bin/rm -f $(FILES)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
