/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:43:34 by wtang             #+#    #+#             */
/*   Updated: 2024/12/19 15:37:12 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	*str;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	str = ft_itoa(n);
	if (!str)
		return ;
	ft_putstr_fd(str, fd);
	free(str);
}
