#include "push_swap.h"

void	push_swap(int *a, int size)
{

}

int	ft_is_number(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (0);
		s++;
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	if (!*s)
		return (0);
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	if (*s == '+')
		s++;
	while (*s)
	{
		num = num * 10 + (*s - '0');
		s++;
	}
	return (num * sign);
}

int	ft_is_int(char *s)
{
	int	num;

	num = ft_atoi(s);
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	return (1);
}

int	ft_is_repeated(char *s)
{
	
}

int	main(int ac, char *av[])
{
	if (ac == 1)
		return (0);
	
}