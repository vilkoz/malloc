# include <unistd.h>

# define WRITE(s) write(1, (s), sizeof((s)))

void		ft_putnbr(int n);
void		ft_putstr(char *s);
