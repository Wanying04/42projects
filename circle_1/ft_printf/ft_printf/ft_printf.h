/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:24:08 by wtang             #+#    #+#             */
/*   Updated: 2025/05/26 19:56:14 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
// # include <stdio.h>

# define HEX_TABLE_LOWER "0123456789abcdef"
# define HEX_TABLE_UPPER "0123456789ABCDEF"

int	ft_print_pointer(void *ptr);
int	ft_print_hex_lower(int num);
int	ft_print_hex_upper(int num);
int	ft_print_decimal(int num);
int	ft_print_decimal_unsigned(unsigned int num);
int	ft_printf(char const *str, ...);

#endif