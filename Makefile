NAME=libft_malloc.so

all: $(NAME)

SRC_DIR=src/

BIN_DIR=bin/

INCLUDE_DIR=include/

INCLUDES_FILES=block.h							\
			   libmalloc.h						\
			   limit.h							\

INCLUDES=$(addprefix $(INCLUDE_DIR), $(INCLUDES_FILES))

SRC_FILES=malloc.c							\
		  free.c							\
		  request_block.c					\
		  realloc.c							\
		  show_alloc_mem.c					\
		  zones.c							\
		  output.c							\

SRC=$(addprefix $(SRC_DIR), $(SRC_FILES))

BINS=$(addprefix $(BIN_DIR), $(SRC:.c=.o))

FLAGS=-Wall -Wextra -Werror -fPIC -g
ifneq ($(D),)
	FLAGS += -DDEBUG_PRINT=1
endif
# FLAGS=-Wall -Wextra -Werror -fPIC -g

LINKER_FLAGS=-shared

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

$(BIN_DIR)%.o: %.c $(INCLUDES)
	@mkdir -p $(shell dirname $@)
	gcc $(FLAGS) -I $(INCLUDE_DIR) -c -o $@ $<

$(NAME): $(BINS)
	gcc $(FLAGS) $(LINKER_FLAGS) -o libft_malloc_$(HOSTTYPE).so $(BINS)
	ln -fs libft_malloc_$(HOSTTYPE).so $(NAME)

clean:
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f libft_malloc_$(HOSTTYPE).so

re: fclean all

test: re $(NAME)
	make -C test re
	make -C test run

test_trace: $(NAME)
	make -C test re
	make -C test trace

test_strace: $(NAME)
	make -C test re
	make -C test strace

.PHONY: re fclean clean all test test_trace test_strace
