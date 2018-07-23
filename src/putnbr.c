#include <unistd.h>

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putnb(long long num)
{
	if (num < 10)
		ft_putchar(num + '0');
	if (num >= 10)
	{
		ft_putnb((num / 10));
		ft_putchar((num % 10) + '0');
	}
}

void		ft_putnbr(int n)
{
	long long	num;

	num = n;
	if (n < 0)
	{
		ft_putchar('-');
		num *= -1;
	}
	ft_putnb(num);
}

void		ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	write(0, s, i);
}
