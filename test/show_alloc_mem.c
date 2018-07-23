#include "libmalloc.h"
#include "test.h"
#include <dlfcn.h>

int		show_alloc_mem_test(void)
{
	void		*b[3];
	void		*handle;
	void		(*show_alloc_mem)(void);

	handle = dlopen("../libmalloc.so", RTLD_LAZY);
	show_alloc_mem = (void (*)(void))dlsym(handle, "show_alloc_mem");
	b[0] = malloc(64);
	RETURN_IF(b[0] == NULL);
	b[1] = malloc(200 + 1);
	RETURN_IF(b[1] == NULL);
	b[2] = malloc(820 + 1);
	RETURN_IF(b[2] == NULL);
	show_alloc_mem();
	free(b[2]);
	show_alloc_mem();
	free(b[0]);
	free(b[1]);
	return (1);
}
