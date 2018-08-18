/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:42:49 by vrybalko          #+#    #+#             */
/*   Updated: 2018/08/18 14:42:49 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmalloc.h"
#include "block.h"
#include <stdio.h>
#include "output.h"

static const char	*g_zone_name[3] = {
	"TINY",
	"SMALL",
	"LARGE"
};

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

static size_t		print_zone(t_zone_type zone)
{
	t_block_meta	**base;
	t_block_meta	*current;
	size_t			total;

	total = 0;
	base = get_block_base();
	PUTSTR(g_zone_name[zone]);
	WRITE(": \n");
	current = base[zone];
	while (current)
	{
		PUTHEX(current + META_SIZE);
		WRITE(" - ");
		PUTHEX(current + current->size + META_SIZE);
		WRITE(" size: ");
		ft_putnbr(current->size);
		WRITE(", ");
		ft_putstr(current->free ? "free" : "not free");
		WRITE("\n");
		total += current->size;
		current = current->next;
	}
	return (total);
}

void				show_alloc_mem(void)
{
	int			i;
	size_t		total;

	i = -1;
	total = 0;
	while (++i < ZONES_NUM)
		total += print_zone(i);
	WRITE("TOTAL: ");
	ft_putnbr(total);
	WRITE("\n");
}
