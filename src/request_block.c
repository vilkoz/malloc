#include <sys/mman.h>
#include <assert.h>
#include "libmalloc.h"
#include "block.h"

t_block_meta	*request_block(size_t size, t_block_meta *last)
{
	void			*s;
	t_block_meta	*b;

	if (size + META_SIZE < size)
		return (NULL);
	s = mmap(NULL,
			size + META_SIZE,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS,
			-1,
			0);
	if (s == (void*)-1)
		return (NULL);
	b = (t_block_meta*)s;
	b->next = NULL;
	b->free = 1;
	b->magic = META_MAGIC;
	b->size = size;
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

	current = base[block->type];
	last = current;
	while (current && current != block)
	{
		last = current;
		current = current->next;
	}
	assert(current != NULL);
	if (last)
		last->next = current->next;
	if (current == base[block->type])
		base[block->type] = current->next;
	size = block->size + META_SIZE;
	assert(munmap(block, size) != -1);
}
