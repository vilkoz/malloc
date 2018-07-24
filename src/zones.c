#include "libmalloc.h"
#include "block.h"
#include <stdio.h>
#include "output.h"

static size_t		g_alloc_sizes[3] = {
	TINY_MAX_SIZE,
	SMALL_MAX_SIZE,
	0
};

static char			*g_zone_name[3] = {
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

	count = -1;
	last = base[zone];
	while (++count < PREALLOCATE_ZONE_COUNT)
	{
		current = request_block(g_alloc_sizes[zone], last);
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

static void			print_zone(t_zone_type zone)
{
	t_block_meta	**base;
	t_block_meta	*current;

	base = get_block_base();
	ft_putstr(g_zone_name[zone]);
	WRITE(" : \n");
	current = base[zone];
	while (current)
	{
		WRITE("size: ");
		ft_putnbr(current->size);
		WRITE(", ");
		ft_putstr(current->free ? "free" : "not free");
		WRITE("\n");
		current = current->next;
	}
}

void				show_alloc_mem(void)
{
	int			i;

	i = -1;
	while (++i < ZONES_NUM)
		print_zone(i);
}
