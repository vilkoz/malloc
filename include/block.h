#ifndef BLOCK_H
# define BLOCK_H

# include <stddef.h>

typedef struct			s_block_meta
{
	size_t				size;
	struct s_block_meta	*next;
	int					free;
	int					magic;
}						t_block_meta;

# define META_SIZE (sizeof(t_block_meta))
# define META_MAGIC (0x11223344)
# define GET_META_PTR(m) (((t_block_meta*)m) - 1)

#endif
