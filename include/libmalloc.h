#ifndef LIBMALLOC_H
# define LIBMALLOC_H

# include <stddef.h>

void		*malloc(size_t size);
void		free(void *m);
void		*realloc(void *ptr, size_t size);

#endif
