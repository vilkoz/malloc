NAME=tests

all: $(NAME)

SRC=test.c					\
	basic.c					\
	error.c					\
	free.c					\

BINS=$(SRC:.c=.o)

FLAGS=-Wall -Wextra -Werror -g

%.o: %.c
	gcc $(FLAGS) -I ../include/ -c -o $@ $<

$(NAME): $(BINS)
	gcc $(FLAGS) -o $(NAME) -L ../ -lmalloc $(BINS)

clean:
	/bin/rm -f $(BINS)

fclean:
	/bin/rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: re fclean clean all run
