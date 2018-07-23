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

	WRITE("start find_free_block""\n");
	current = g_base[select_zone_type(size)];
	last = NULL;
	WRITE("find_free_block while start""\n");
	if (current)
		WRITE("find_free_block current != NULL""\n");
	else
		WRITE("find_free_block current == NULL""\n");
	while (current && !(current->free == 1 && current->size >= size))
	{
		last = current;
		current = current->next;
	}
	WRITE("find_free_block while end""\n");
	if (current == NULL)
	{
		WRITE("find_free_block request_block start""\n");
		current = request_block(size, last);
		WRITE("find_free_block request_block end""\n");
	}
	if (g_base[select_zone_type(size)] == NULL)
		g_base[select_zone_type(size)] = current;
	WRITE("end find_free_block""\n");
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

void				free(void *m)
{
	t_block_meta	*b;

	if (!m)
		return ;
	WRITE("start free\n");
	b = GET_META_PTR(m);
	assert(b->free == 0);
	assert(b->magic == META_MAGIC);
	WRITE("end assets\n");
	b->free = 1;
	WRITE("set free\n");
	/* if (b->type == ZONE_LARGE) */
	/* { */
	/* 	WRITE("release_block start\n"); */
	/* 	release_block(b, (t_block_meta**)&(g_base[0])); */
	/* 	WRITE("release_block end\n"); */
	/* } */
	WRITE("end free\n");
}

void				*malloc(size_t size)
{
	t_block_meta	*b;

	WRITE("malloc start\n");
	if (g_base[ZONE_TINY] == NULL || g_base[ZONE_SMALL] == NULL)
	{
		WRITE("malloc preallocate start\n");
		preallocate_zones((t_block_meta**)&(g_base[0]));
		WRITE("malloc preallocate end\n");
	}
	if (size == 0)
		return (NULL);
	WRITE("malloc check_limit start\n");
	if (!check_limit(size))
		return (NULL);
	WRITE("malloc check_limit end\n");
	WRITE("malloc find_free_block start\n");
	if ((b = find_free_block(size)) == NULL)
		return (NULL);
	WRITE("malloc find_free_block end\n");
	b->free = 0;
	WRITE("malloc end");
	return ((void*)(b + 1));
}
