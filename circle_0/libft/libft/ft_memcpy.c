/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:05:56 by wtang             #+#    #+#             */
/*   Updated: 2024/12/19 15:20:35 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_s;
	unsigned char	*ptr_d;

	ptr_s = (unsigned char *)src;
	ptr_d = (unsigned char *)dest;
	if (ptr_s == NULL && ptr_d == NULL)
		return (dest);
	while (n--)
	{
		*ptr_d = *ptr_s;
		ptr_s++;
		ptr_d++;
	}
	return (dest);
}
