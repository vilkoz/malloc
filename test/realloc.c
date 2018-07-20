#include "libmalloc.h"
#include "test.h"

int		realloc_test(void)
{
	void		*m;
	void		*n;
	size_t		size;

	size = 0xBEEF;
	m = realloc(NULL, size);
	RETURN_IF(m == NULL);
	n = realloc(m, size);
	RETURN_IF(m != n);
	m = realloc(n, size * 2);
	RETURN_IF(m == n);
	return (1);
}
