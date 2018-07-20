#ifndef TEST_H
# define TEST_H

# include <stdio.h>

typedef int		(*t_test_provider)(void);

int				basic_test(void);
int				error_test(void);
int				free_test(void);
int				realloc_test(void);

#define RETURN_IF(b)															\
			do {																\
				if (b)															\
				{																\
					printf("FAIL on %s:%d\n", __FILE__, __LINE__);		\
					return (0);													\
				}																\
			} while(0)

#endif
