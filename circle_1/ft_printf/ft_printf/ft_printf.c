/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:24:01 by wtang             #+#    #+#             */
/*   Updated: 2025/05/26 19:55:06 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_putstr(char *str)
{
	int	size;

	size = 0;
	if (!str)
	{
		size += write(1, "(null)", 6);
		return (size);
	}
	while (*str)
	{
		size += ft_putchar(*str);
		str++;
	}
	return (size);
}

static int	ft_format(va_list va, const char word)
{
	int	size;

	size = 0;
	if (word == 'c')
		size += ft_putchar(va_arg(va, int));
	else if (word == 's')
		size += ft_putstr(va_arg(va, char *));
	else if (word == 'p')
		size += ft_print_pointer(va_arg(va, void *));
	else if (word == 'd' || word == 'i')
		size += ft_print_decimal(va_arg(va, int));
	else if (word == 'u')
		size += ft_print_decimal_unsigned(va_arg(va, unsigned int));
	else if (word == 'x')
		size += ft_print_hex_lower(va_arg(va, int));
	else if (word == 'X')
		size += ft_print_hex_upper(va_arg(va, int));
	else if (word == '%')
		size += ft_putchar('%');
	return (size);
}

int	ft_printf(char const *str, ...)
{
	va_list	va;
	int		size;

	if (!str)
		return (0);
	size = 0;
	va_start(va, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str)
				size += ft_format(va, *str);
		}
		else
		{
			size += ft_putchar(*str);
		}
		str++;
	}
	va_end(va);
	return (size);
}
