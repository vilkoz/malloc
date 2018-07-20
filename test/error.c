#include "libmalloc.h"

int		error_test(void)
{
	void		*m;

	m = malloc(0xFFFFFFFFFFFFFFFFULL);
	return m == NULL;
}
