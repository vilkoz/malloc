#include <libmalloc.h>
#include <string.h>
#include "test.h"

static int		check(void *m, unsigned int size)
{
	unsigned int	i;
	unsigned char	*s;

	s = (unsigned char*)m;
	i = 0;
	while (i < size)
	{
		RETURN_IF(s[i] != 'c');
		i++;
	}
	return (1);
}

int				basic_test(void)
{
	void			*m;
	unsigned int	size;

	size = 0xFFFFFF;
	m = malloc(size);
	memset(m, 'c', size);
	return check(m, size);
}
