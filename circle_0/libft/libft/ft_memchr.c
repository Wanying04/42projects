/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:17:25 by wtang             #+#    #+#             */
/*   Updated: 2024/12/19 15:23:11 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;
	unsigned char	ptr_c;

	ptr_s = (unsigned char *)s;
	ptr_c = (unsigned char)c;
	while (n--)
	{
		if (*ptr_s == ptr_c)
			return ((void *)ptr_s);
		ptr_s++;
	}
	return (NULL);
}
