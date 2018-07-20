#include "libmalloc.h"

int		error_test(void)
{
	void		*m;

	m = malloc(0xFFFFFFFFFFFFFFFF);
	return m == NULL;
}
