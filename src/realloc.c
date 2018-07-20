#include "libmalloc.h"
#include "block.h"
#include <assert.h>
#include <string.h>

void		*realloc(void *ptr, size_t size)
{
	t_block_meta	*b;
	void			*p;

	return (NULL);
	if (!ptr)
		return (malloc(size));
	b = GET_META_PTR(ptr);
	assert(b->magic == META_MAGIC);
	if (b->size >= size)
		return (ptr);
	if ((p = malloc(size)) == NULL)
		return (NULL);
	memcpy(p, ptr, b->size);
	free(ptr);
	return(p);
}
