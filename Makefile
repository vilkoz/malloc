NAME=libmalloc.a

all: $(NAME)

SRC_DIR=src/

BIN_DIR=bin/

INCLUDE_DIR=include/

SRC_FILES=malloc.c

SRC=$(addprefix $(SRC_DIR), $(SRC_FILES))

BINS=$(addprefix $(BIN_DIR), $(SRC:.c=.o))

FLAGS=-Wall -Wextra -Werror -g

$(BIN_DIR)%.o: %.c
	@mkdir -p $(shell dirname $@)
	gcc $(FLAGS) -I $(INCLUDE_DIR) -c -o $@ $<

$(NAME): $(BINS)
	ar -rs $(NAME) $(BINS)

clean:
	/bin/rm -f $(BINS)

fclean:
	/bin/rm -f $(NAME)

re: fclean all

test: $(NAME)
	make -C test run

.PHONY: re fclean clean all test
