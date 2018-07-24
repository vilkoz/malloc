#ifndef LIBMALLOC_H
# define LIBMALLOC_H

# include <stddef.h>

# ifdef DEBUG
#  define malloc(a) my_malloc(a)
#  define free(a) my_free(a)
#  define realloc(...) my_realloc(__VA_ARGS__)
#  define DEBUG_NAME(n) my_##n
# else
#  define DEBUG_NAME(n) n
# endif

void		*DEBUG_NAME(malloc)(size_t size);
void		DEBUG_NAME(free)(void *m);
void		*DEBUG_NAME(realloc)(void *ptr, size_t size);
void		show_alloc_mem(void);

#endif
