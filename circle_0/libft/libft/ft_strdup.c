/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:05:33 by wtang             #+#    #+#             */
/*   Updated: 2024/12/19 15:24:57 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	total;
	void	*z;
	char	*z_new;

	total = ft_strlen(s) + 1;
	z = malloc(total);
	if (z == NULL)
		return (NULL);
	z_new = (char *)z;
	while (*s != '\0')
	{
		*z_new = *s;
		s++;
		z_new++;
	}
	*z_new = '\0';
	return ((char *)z);
}
