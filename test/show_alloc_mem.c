#include "libmalloc.h"
#include "test.h"

int		show_alloc_mem_test(void)
{
	void		*b[3];

	b[0] = malloc(64);
	RETURN_IF(b[0] == NULL);
	b[1] = malloc(2048 + 1);
	RETURN_IF(b[1] == NULL);
	b[2] = malloc(4096 + 1);
	RETURN_IF(b[2] == NULL);
	show_alloc_mem();
	free(b[2]);
	free(b[1]);
	free(b[0]);
	return (1);
}
