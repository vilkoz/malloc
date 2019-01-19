/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:42:49 by vrybalko          #+#    #+#             */
/*   Updated: 2019/01/19 16:47:34 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmalloc.h"
#include "block.h"
#include "output.h"

t_zone_type			select_zone_type(size_t size)
{
	if (size <= TINY_MAX_SIZE)
		return (ZONE_TINY);
	if (size <= SMALL_MAX_SIZE)
		return (ZONE_SMALL);
	return (ZONE_LARGE);
}

static void			allocate_zone(t_zone_type zone, t_block_meta **base)
{
	t_block_meta		*current;
	t_block_meta		*last;
	int					count;
	int					page_size;

	page_size = getpagesize();
	count = -1;
	last = base[zone];
	while (++count < PREALLOCATE_ZONE_COUNT)
	{
		current = request_block(page_size * (zone + 1), last);
		current->type = zone;
		current->free = 1;
		current->size = page_size * (zone + 1);
		last = current;
		if (base[zone] == NULL)
			base[zone] = last;
	}
}

void				preallocate_zones(t_block_meta **base)
{
	allocate_zone(ZONE_TINY, base);
	allocate_zone(ZONE_SMALL, base);
}
