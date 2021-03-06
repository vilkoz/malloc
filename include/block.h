/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:44:00 by vrybalko          #+#    #+#             */
/*   Updated: 2019/01/19 17:08:25 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_H
# define BLOCK_H

# include <stddef.h>

typedef struct			s_block_meta
{
	struct s_block_meta	*next;
	size_t				size;
	int					free;
	int					magic;
	int					type;
}						t_block_meta;

typedef enum			e_zone_type
{
	ZONE_TINY,
	ZONE_SMALL,
	ZONE_LARGE,
	ZONES_NUM
}						t_zone_type;

# define META_SIZE (sizeof(t_block_meta))
# define META_MAGIC (0x11223344)
# define GET_META_PTR(m) (((t_block_meta*)m) - 1)
# define TINY_MAX_SIZE (2048)
# define SMALL_MAX_SIZE (4096)
# define PREALLOCATE_ZONE_COUNT (3)

t_block_meta			*request_block(size_t size, t_block_meta *last);
t_zone_type				select_zone_type(size_t size);
t_block_meta			**get_block_base(void);
void					preallocate_zones(t_block_meta **base);
void					release_block(t_block_meta *block,
							t_block_meta **base);
int						is_pointer_valid(void *p);

#endif
