#include "libmalloc.h"
#include <string.h>

int		free_test(void)
{
	void		*m;

	m = malloc(0xDEAD);
	memset(m, 'D', 0xDEAD);
	free(m);
	return 1;
}
