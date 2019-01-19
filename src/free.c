/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 16:56:58 by vrybalko          #+#    #+#             */
/*   Updated: 2019/01/19 17:08:19 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limit.h"
#include "libmalloc.h"
#include "block.h"
#include "output.h"
#include <pthread.h>

extern pthread_mutex_t	g_malloc_mutex;

static int				zone_search_block(t_block_meta *zone, void *p)
{
	t_block_meta		*current;

	current = zone;
	while (current)
	{
		if ((void*)(current + 1) == p)
			return (1);
		current = current->next;
	}
	return (0);
}

int						is_pointer_valid(void *p)
{
	int				res;
	t_block_meta	**base;

	base = get_block_base();
	res = zone_search_block(base[0], p) || zone_search_block(base[1], p)
			|| zone_search_block(base[2], p);
	return res;
}

static t_block_meta		*validate_block(void *m)
{
	t_block_meta	*b;

	if (!m)
		return (NULL);
	b = GET_META_PTR(m);
	if (!is_pointer_valid(m))
	{
		IF_DEBUG(WRITE("INVALID POINTER!\n"));
		return (NULL);
	}
	if (b->free != 0)
	{
		IF_DEBUG(WRITE("DOUBLE FREE!\n"));
		return (NULL);
	}
	if (b->magic != META_MAGIC)
	{
		IF_DEBUG(WRITE("CORRUPTED POINTER: MAGIC("));
		IF_DEBUG(PUTHEX(b->magic));
		IF_DEBUG(WRITE(")\n"));
		return (NULL);
	}
	return (b);
}

void					free(void *m)
{
	t_block_meta	*b;

	pthread_mutex_lock(&g_malloc_mutex);
	if ((b = validate_block(m)) == NULL)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return ;
	}
	b->free = 1;
	if (b->type == ZONE_LARGE)
	{
		release_block(b, get_block_base());
	}
	pthread_mutex_unlock(&g_malloc_mutex);
}
