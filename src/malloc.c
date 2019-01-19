/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:42:49 by vrybalko          #+#    #+#             */
/*   Updated: 2019/01/19 18:31:19 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limit.h"
#include "libmalloc.h"
#include "block.h"
#include <assert.h>
#include <pthread.h>
#include "output.h"

static void			*g_base[3] = {NULL, NULL, NULL};
pthread_mutex_t		g_malloc_mutex;

static void			split_block(t_block_meta *b, size_t size)
{
	t_block_meta		*new_block;

	if (b->size - size < META_SIZE * 2)
		return ;
	new_block = (void*)(b + 1) + size;
	new_block->size = b->size - META_SIZE * 2 - size;
	new_block->type = b->type;
	new_block->magic = b->magic;
	new_block->next = b->next;
	new_block->free = 1;
	b->next = new_block;
	b->size = size;
}

static t_block_meta	*find_free_block(size_t size)
{
	t_block_meta		*last;
	t_block_meta		*current;
	size_t				tmp_size;

	current = g_base[select_zone_type(size)];
	last = NULL;
	while (current && !(current->free == 1 && current->size >= size))
	{
		last = current;
		current = current->next;
	}
	if (current == NULL)
	{
		if (select_zone_type(size) != ZONE_LARGE)
			tmp_size = (select_zone_type(size) + 1) * 4096 - META_SIZE;
		else
			tmp_size = size;
		current = request_block(tmp_size, last);
		if (current)
			current->type = select_zone_type(size);
	}
	if (current->size > size)
		split_block(current, size);
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

void				*malloc(size_t size)
{
	t_block_meta	*b;

	pthread_mutex_lock(&g_malloc_mutex);
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
	pthread_mutex_unlock(&g_malloc_mutex);
	return ((void*)(b + 1));
}
