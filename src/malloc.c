#include "limit.h"
#include "libmalloc.h"
#include "block.h"
#include <stdio.h>
#include <assert.h>

#include "output.h"

static void			*g_base[3] = {NULL, NULL, NULL};

static t_block_meta	*find_free_block(size_t size)
{
	t_block_meta		*last;
	t_block_meta		*current;

	current = g_base[select_zone_type(size)];
	last = NULL;
	while (current && !(current->free == 1 && current->size >= size))
	{
		last = current;
		current = current->next;
	}
	if (current == NULL)
	{
		current = request_block(size, last);
		if (current)
			current->type = select_zone_type(size);
	}
	if (g_base[select_zone_type(size)] == NULL)
		g_base[select_zone_type(size)] = current;
	return (current);
}

static int			check_limit(size_t size)
{
	t_rlimit		rlimit;

	if (getrlimit(RLIMIT_AS, &rlimit) == -1 || rlimit.rlim_cur < size)
		return (0);
	if (getrlimit(RLIMIT_DATA, &rlimit) == -1 || rlimit.rlim_cur < size)
		return (0);
	return (1);
}

t_block_meta		**get_block_base(void)
{
	return ((t_block_meta**)&(g_base[0]));
}

void				DEBUG_NAME(free)(void *m)
{
	t_block_meta	*b;

	if (!m)
		return ;
	b = GET_META_PTR(m);
	if (b->free != 0)
		return (void)IF_DEBUG(WRITE("DOUBLE FREE!\n"));
	if (b->magic != META_MAGIC)
	{
		IF_DEBUG(WRITE("CORRUPTED POINTER: MAGIC("));
		IF_DEBUG(PUTHEX(b->magic));
		IF_DEBUG(WRITE(")\n"));
	}
	b->free = 1;
	if (b->type == ZONE_LARGE)
	{
		release_block(b, (t_block_meta**)&(g_base[0]));
	}
}

void				*DEBUG_NAME(malloc)(size_t size)
{
	t_block_meta	*b;

	if (g_base[ZONE_TINY] == NULL || g_base[ZONE_SMALL] == NULL)
	{
		preallocate_zones((t_block_meta**)&(g_base[0]));
	}
	if (size == 0)
		return (NULL);
	if (!check_limit(size))
		return (NULL);
	if ((b = find_free_block(size)) == NULL)
		return (NULL);
	b->free = 0;
	return ((void*)(b + 1));
}
