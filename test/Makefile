NAME=tests

all: $(NAME)

SRC=test.c					\
	basic.c					\
	error.c					\
	free.c					\
	realloc.c				\

BINS=$(SRC:.c=.o)

FLAGS=-Wall -Wextra -Werror -g

%.o: %.c
	gcc $(FLAGS) -I ../include/ -c -o $@ $<

$(NAME): $(BINS)
	gcc $(FLAGS) -o $(NAME) $(BINS)

clean:
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

run: $(NAME)
	LD_PRELOAD=../libmalloc.so ./$(NAME)

.PHONY: re fclean clean all run
