
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}

int	ft_putnbr_base(unsigned long n, char *base)
{
	int	len;

	len = 0;
	if (n >= 16)
		len += ft_putnbr_base(n / 16, base);
	len += ft_putchar(base[n % 16]);
	return (len);
}

int	ft_putnbr(int n)
{
	long	nb;
	int		len;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb *= (-1);
	}
	if (nb >= 10)
		len += ft_putnbr(nb / 10);
	len += ft_putchar(nb % 10 + '0');
	return (len);
}

static int	ft_check(va_list arg, char c)
{
	int	l;

	l = 0;
	if (c == 's')
		l += ft_putstr(va_arg(arg, char *));
    else if (c == 'd')
		l += ft_putnbr(va_arg(arg, int));
	else if (c == '%')
		l += ft_putchar('%');
	else if (c == 'x')
		l += ft_putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		l += ft_putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF");
	else if (c != '\0')
		l += ft_putchar(c);
	return (l);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += ft_check(args, str[i]);
		}
		else
			len += ft_putchar(str[i]);
		if (str[i] == '\0')
			break ;
		i++;
	}
	va_end(args);
	return (len);
}

int main()
{
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
}