#include "libmalloc.h"
#include "test.h"

int		error_test(void)
{
	void		*m;

	m = malloc(0xFFFFFFFFFFFFFFFFULL);
	RETURN_IF(m != NULL);
	m = malloc(0xFFFFFFFFFFFFFFFULL);
	RETURN_IF(m != NULL);
	m = malloc(0xFFFFFFFFFFFFFFULL);
	RETURN_IF(m != NULL);
	m = malloc(0xFFFFFFFFFFFFFULL);
	RETURN_IF(m != NULL);
	m = malloc(0xFFFFFFFFULL);
	RETURN_IF(m == NULL);
	return (1);
}
