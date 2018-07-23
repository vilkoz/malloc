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
	gcc $(FLAGS) -o $(NAME) $(BINS) -ldl

clean:
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)
	LD_PRELOAD=../libmalloc.so ./$(NAME)

trace: $(NAME)
	ltrace env LD_PRELOAD=../libmalloc.so ./$(NAME)
	# ltrace ./$(NAME)

strace: $(NAME)
	strace env LD_PRELOAD=../libmalloc.so ./$(NAME)
	# strace ./$(NAME)

.PHONY: re fclean clean all run trace strace
