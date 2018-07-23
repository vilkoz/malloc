#include <string.h>
#include <stdio.h>
#include "test.h"

static const t_test_provider	g_tests[] = {
	basic_test,
	error_test,
	free_test,
	realloc_test,
	show_alloc_mem_test,
	NULL
};

int main(void)
{
	int		i;

	i = -1;
	while (g_tests[++i] != NULL)
	{
		if (g_tests[i]())
			printf("test #%d: OK\n", i);
		else
			printf("test #%d: FAIL\n", i);
	}
}
