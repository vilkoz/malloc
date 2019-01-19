/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:42:49 by vrybalko          #+#    #+#             */
/*   Updated: 2019/01/19 17:13:45 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmalloc.h"
#include "block.h"
#include "output.h"
#include <assert.h>
#include <string.h>
#include <pthread.h>

extern pthread_mutex_t	g_malloc_mutex;

static t_block_meta		*validate_block(void *ptr)
{
	t_block_meta	*b;

	b = GET_META_PTR(ptr);
	if (b->free != 0)
	{
		IF_DEBUG(WRITE("realloc: POINTER WAS NOT ALLOCATED!\n"));
		return (NULL);
	}
	if (b->magic != META_MAGIC)
	{
		IF_DEBUG(WRITE("realloc: CORRUPTED POINTER!\n"));
		return (NULL);
	}
	return (b);
}

void					*realloc(void *ptr, size_t size)
{
	t_block_meta	*b;
	void			*p;

	if (!ptr)
		return (malloc(size));
	pthread_mutex_lock(&g_malloc_mutex);
	if ((b = validate_block(ptr)) == NULL)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return (NULL);
	}
	if (b->size >= size)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return (ptr);
	}
	pthread_mutex_unlock(&g_malloc_mutex);
	if ((p = malloc(size)) == NULL)
		return (NULL);
	memcpy(p, ptr, b->size);
	free(ptr);
	return (p);
}
