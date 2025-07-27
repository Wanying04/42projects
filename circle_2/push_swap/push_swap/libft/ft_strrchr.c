/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:17:15 by wtang             #+#    #+#             */
/*   Updated: 2024/12/19 15:22:28 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;

	ptr = s;
	while (*ptr != '\0')
	{
		ptr++;
	}
	if ((char)c == '\0')
		return ((char *)ptr);
	while (ptr != s)
	{
		ptr--;
		if (*ptr == (char)c)
			return ((char *)ptr);
	}
	return (NULL);
}
