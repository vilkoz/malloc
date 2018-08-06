NAME=tests

all: $(NAME)

SRC=test.c					\
	basic.c					\
	error.c					\
	free.c					\
	realloc.c				\
	show_alloc_mem.c		\

BINS=$(SRC:.c=.o)

FLAGS=-Wall -Wextra -Werror -g -DDEBUG

%.o: %.c
	gcc $(FLAGS) -I ../include/ -c -o $@ $<

$(NAME): $(BINS)
	gcc $(FLAGS) -o $(NAME) $(BINS) -L.. -lft_malloc

clean:
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

run: $(NAME)
	LD_LIBRARY_PATH=../ ./$(NAME)

trace: $(NAME)
	ltrace env LD_LIBRARY_PATH=../ ./$(NAME)

strace: $(NAME)
	strace env LD_LIBRARY_PATH=../ ./$(NAME)

.PHONY: re fclean clean all run trace strace
