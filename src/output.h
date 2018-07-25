#ifndef OUTPUT_H
# define OUTPUT_H

# include <unistd.h>

# define WRITE(s) write(1, (s), sizeof((s)))
# define PUTSTR(s) ft_putstr((char*)(s))
# define PUTHEX(s) ft_puthex((unsigned long long)(s))
# ifndef DEBUG_PRINT
#  define DEBUG_PRINT 1
# endif
# define IF_DEBUG(s) (void)((DEBUG_PRINT) ? (s) : 0)

void		ft_putnbr(long long n);
void		ft_putstr(char *s);
void		ft_puthex(unsigned long long n);

#endif
