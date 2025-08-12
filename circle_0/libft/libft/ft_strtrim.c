/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:13:13 by wtang             #+#    #+#             */
/*   Updated: 2024/12/19 15:26:04 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	total;
	size_t	i;
	char	*z;

	start = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	total = end - start;
	if (total == 0)
		return (ft_strdup(""));
	z = malloc(total + 1);
	if (z == NULL)
		return (NULL);
	while (start < end)
		z[i++] = s1[start++];
	z[i] = '\0';
	return (z);
}
