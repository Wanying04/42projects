/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:03:19 by wtang             #+#    #+#             */
/*   Updated: 2025/06/19 19:26:15 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char *src)
{
	char	*dup;
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(src) + 1;
	dup = (char *)malloc(size * sizeof(char)); //ERROR: size = (char *)malloc((ft_strlen(src) + 1)*sizeof(char));
	if (dup == NULL) //ERROR: if (size == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dup[i] = src[i]; //ERROR: *dup = src[i];
		i++;
	}
	dup[i] = '\0'; //FORGOTTEN
	return (dup); //ERROR: return (*dup);
}
