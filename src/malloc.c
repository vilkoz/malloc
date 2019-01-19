/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:42:49 by vrybalko          #+#    #+#             */
/*   Updated: 2019/01/19 17:02:29 by vrybalko         ###   ########.fr       */
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
