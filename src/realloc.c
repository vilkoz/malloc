/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:42:49 by vrybalko          #+#    #+#             */
/*   Updated: 2018/08/18 14:42:49 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmalloc.h"
#include "block.h"
#include "output.h"
#include <assert.h>
#include <string.h>

void		*realloc(void *ptr, size_t size)
{
	t_block_meta	*b;
	void			*p;

	if (!ptr)
		return (malloc(size));
	b = GET_META_PTR(ptr);
	assert(b->magic == META_MAGIC);
	assert(b->free == 0);
	if (b->magic != META_MAGIC)
	{
		IF_DEBUG(WRITE("CORRUPTED POINTER!\n"));
		return (NULL);
	}
	if (b->size >= size)
		return (ptr);
	if ((p = malloc(size)) == NULL)
		return (NULL);
	memcpy(p, ptr, b->size);
	free(ptr);
	return (p);
}
