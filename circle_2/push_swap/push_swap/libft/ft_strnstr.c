/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:51:46 by wtang             #+#    #+#             */
/*   Updated: 2024/12/19 15:23:38 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	t;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	if (*big == '\0')
		return (NULL);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			t = 0;
			while (little[t] != '\0' && big[i + t] == little[t] && i + t < len)
			{
				t++;
			}
			if (little[t] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
