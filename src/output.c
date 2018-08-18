/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:42:49 by vrybalko          #+#    #+#             */
/*   Updated: 2018/08/18 14:42:49 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	write(0, s, i);
}

void		ft_putnbr(long long n)
{
	long long		copy;
	int				i;
	char			buf[23];

	if (n == 0)
		return (void)ft_putstr("0");
	i = -1;
	if (n < 0)
	{
		n = -n;
		if (n < 0)
			return (void)ft_putstr("-9223372036854775808");
		buf[++i] = '-';
	}
	copy = n;
	while (copy > 0 && (++i || 1))
		copy /= 10;
	buf[i + 1] = 0;
	while (n > 0)
	{
		buf[i] = (n % 10) + '0';
		i--;
		n /= 10;
	}
	ft_putstr(&(buf[0]));
}

void		ft_puthex(unsigned long long n)
{
	static const char	chars[] = "0123456789ABCDEF";
	char				buf[sizeof(unsigned long long) * 8 + 1 + 2];
	int					i;
	unsigned long long	copy;

	if (n == 0)
		return (void)ft_putstr("0x0");
	copy = n;
	buf[0] = '0';
	buf[1] = 'x';
	i = -1 + 2;
	while (copy > 0)
	{
		copy >>= 4;
		i++;
	}
	buf[i + 1] = 0;
	while (n > 0)
	{
		buf[i] = chars[n & 0xF];
		i--;
		n >>= 4;
	}
	ft_putstr(&(buf[0]));
}
