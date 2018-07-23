NAME=libmalloc.so

all: $(NAME)

SRC_DIR=src/

BIN_DIR=bin/

INCLUDE_DIR=include/

SRC_FILES=malloc.c							\
		  realloc.c							\

SRC=$(addprefix $(SRC_DIR), $(SRC_FILES))

BINS=$(addprefix $(BIN_DIR), $(SRC:.c=.o))

FLAGS=-Wall -Wextra -Werror -fPIC -g

LINKER_FLAGS=-shared

$(BIN_DIR)%.o: %.c
	@mkdir -p $(shell dirname $@)
	gcc $(FLAGS) -I $(INCLUDE_DIR) -c -o $@ $<

$(NAME): $(BINS)
	gcc $(FLAGS) $(LINKER_FLAGS) -o $(NAME) $(BINS)

clean:
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

test: $(NAME)
	make -C test re
	make -C test run

.PHONY: re fclean clean all test
