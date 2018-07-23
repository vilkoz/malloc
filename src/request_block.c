#include <sys/mman.h>
#include <assert.h>
#include "libmalloc.h"
#include "block.h"

# include <unistd.h>

# define WRITE(s) write(1, s, sizeof(s))

t_block_meta	*request_block(size_t size, t_block_meta *last)
{
	void			*s;
	t_block_meta	*b;

	if (size + META_SIZE < size)
		return (NULL);
	s = mmap(NULL,
			size + META_SIZE,
			PROT_READ|PROT_WRITE,
			MAP_PRIVATE|MAP_ANONYMOUS,
			-1,
			0);
	if (s == (void*)-1)
		return (NULL);
	b = (t_block_meta*)s;
	b->next = NULL;
	b->free = 1;
	b->magic = META_MAGIC;
	b->size = size;
	b->type = select_zone_type(size);
	if (last)
		last->next = b;
	return (b);
}

void			release_block(t_block_meta *block,
					t_block_meta **base)
{
	t_block_meta		*current;
	t_block_meta		*last;
	size_t				size;

	WRITE("release block start\n");
	current = base[block->type];
	last = NULL;
	WRITE("release block while start\n");
	while (current && current != block)
	{
		last = current;
		current = current->next;
	}
	WRITE("release block while end\n");
	assert(current != NULL);
	WRITE("release block check last\n");
	if (last)
	{
		last->next = NULL;
	}
	WRITE("release block check last end\n");
	WRITE("release block munmap\n");
	size = block->size + META_SIZE;
	assert(munmap(block, size) != -1);
	WRITE("release block munmap end\n");
}
