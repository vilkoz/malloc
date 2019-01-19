/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 16:46:17 by vrybalko          #+#    #+#             */
/*   Updated: 2019/01/19 16:47:19 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmalloc.h"
#include "block.h"
#include "output.h"

static const char	*g_zone_name[3] = {
	"TINY",
	"SMALL",
	"LARGE"
};

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
