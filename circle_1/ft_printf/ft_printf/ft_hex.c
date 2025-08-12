/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:23:47 by wtang             #+#    #+#             */
/*   Updated: 2025/05/26 18:13:17 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_recursion(unsigned long address)
{
	int	remainder;
	int	size;

	size = 0;
	if (address >= 16)
		size += ft_recursion(address / 16);
	remainder = address % 16;
	if (remainder < 10)
		size += write(1, &(char){remainder + '0'}, 1);
	else
		size += write(1, &(char){remainder - 10 + 'a'}, 1);
	return (size);
}

int	ft_print_pointer(void *ptr)
{
	unsigned long	address;
	int				size;

	address = (unsigned long)ptr;
	size = 0;
	if (!ptr)
		size += write(1, "(nil)", 5);
	else
	{
		size += write(1, "0x", 2);
		size += ft_recursion(address);
	}
	return (size);
}

int	ft_print_hex_lower(int num)
{
	unsigned int	unum;
	int				i;
	int				size;
	char			c;

	unum = (unsigned int)num;
	i = 7;
	size = 0;
	while (i >= 0)
	{
		c = HEX_TABLE_LOWER[(unum >> (i * 4)) & 0xF];
		if (c != '0' || size > 0 || i == 0)
			size += write(1, &c, 1);
		i--;
	}
	return (size);
}

int	ft_print_hex_upper(int num)
{
	unsigned int	unum;
	int				i;
	int				size;
	char			c;

	unum = (unsigned int)num;
	i = 7;
	size = 0;
	while (i >= 0)
	{
		c = HEX_TABLE_UPPER[(unum >> (i * 4)) & 0xF];
		if (c != '0' || size > 0 || i == 0)
			size += write(1, &c, 1);
		i--;
	}
	return (size);
}
