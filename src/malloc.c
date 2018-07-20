#include <sys/mman.h>
#include "limit.h"
#include "libmalloc.h"
#include "block.h"
#include <stdio.h>
#include <assert.h>

static void			*g_base = NULL;

static t_block_meta	*request_block(size_t size, t_block_meta *last)
{
	void			*s;
	t_block_meta	*b;

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
	b->free = 0;
	b->magic = META_MAGIC;
	b->size = size;
	if (last)
		last->next = b;
	return (b);
}

static t_block_meta	*find_free_block(size_t size)
{
	t_block_meta		*last;
	t_block_meta		*current;

	current = g_base;
	last = NULL;
	while (current && !(current->free == 1 && current->size >= size))
	{
		last = current;
		current = current->next;
	}
	if (current == NULL)
	{
		current = request_block(size, last);
	}
	return (current);
}

static int			check_limit(size_t size)
{
	t_rlimit		rlimit;

	if (getrlimit(RLIMIT_AS, &rlimit) == -1)
		return (0);
	printf("1 rlmit cur: %zu\n", rlimit.rlim_cur);
	if (rlimit.rlim_cur < size)
		return (0);
	if (getrlimit(RLIMIT_DATA, &rlimit) == -1)
		return (0);
	printf("2 rlmit cur: %zu\n", rlimit.rlim_cur);
	if (rlimit.rlim_cur < size)
		return (0);
	return (1);
}

void				free(void *m)
{
	t_block_meta	*b;

	if (!m)
		return ;
	b = GET_META_PTR(m);
	assert(b->free == 0);
	assert(b->magic == META_MAGIC);
	b->free = 1;
}

void				*malloc(size_t size)
{
	t_block_meta	*b;

	if (size == 0)
		return (NULL);
	if (!check_limit(size))
		return (NULL);
	if ((b = find_free_block(size)) == NULL)
		return (NULL);
	if (g_base == NULL)
		g_base = b;
	return ((void*)(b + 1));
}
