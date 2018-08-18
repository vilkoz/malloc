/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmalloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:44:00 by vrybalko          #+#    #+#             */
/*   Updated: 2018/08/18 14:44:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMALLOC_H
# define LIBMALLOC_H

# include <stddef.h>

void		*malloc(size_t size);
void		free(void *m);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem(void);

#endif
