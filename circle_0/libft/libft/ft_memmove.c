/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:44:55 by wtang             #+#    #+#             */
/*   Updated: 2024/12/19 15:20:47 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_s;
	unsigned char	*ptr_d;
	size_t			i;

	i = 0;
	ptr_s = (unsigned char *)src;
	ptr_d = (unsigned char *)dest;
	if (ptr_s == NULL && ptr_d == NULL)
		return (dest);
	if (ptr_d > ptr_s && ptr_d < ptr_s + n)
	{
		i = n;
		while (i--)
			ptr_d[i] = ptr_s[i];
	}
	else
	{
		while (i < n)
		{
			ptr_d[i] = ptr_s[i];
			i++;
		}
	}
	return (dest);
}
