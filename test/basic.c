#include <libmalloc.h>
#include <string.h>
#include "test.h"
#include <dlfcn.h>

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
	int				res;
	void		*handle;
	void		(*show_alloc_mem)(void);

	handle = dlopen("../libmalloc.so", RTLD_LAZY);
	show_alloc_mem = (void (*)(void))dlsym(handle, "show_alloc_mem");

	size = 0xFFFFFF;
	show_alloc_mem();
	m = malloc(size);
	show_alloc_mem();
	memset(m, 'c', size);
	res = check(m, size);
	free(m);
	return (res);
}
