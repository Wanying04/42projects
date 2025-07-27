/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:23:50 by wtang             #+#    #+#             */
/*   Updated: 2025/03/27 14:19:11 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_recursion(unsigned int num)
{
	int		size;
	char	c;

	size = 0;
	if (num >= 10)
		size += ft_recursion(num / 10);
	c = (num % 10) + '0';
	size += write(1, &c, 1);
	return (size);
}

int	ft_print_decimal(int num)
{
	int	size;

	size = 0;
	if (num == -2147483648)
	{
		size += write(1, "-2147483648", 11);
		return (size);
	}
	if (num == 0)
	{
		size += write(1, "0", 1);
		return (size);
	}
	if (num < 0)
	{
		size += write(1, "-", 1);
		num = -num;
	}
	size += ft_recursion(num);
	return (size);
}

int	ft_print_decimal_unsigned(unsigned int num)
{
	int	size;

	size = 0;
	if (num == 0)
	{
		size += write(1, "0", 1);
		return (size);
	}
	size += ft_recursion(num);
	return (size);
}
