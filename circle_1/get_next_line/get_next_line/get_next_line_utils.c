/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:07:09 by wtang             #+#    #+#             */
/*   Updated: 2025/05/18 16:11:11 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total;
	char	*z;
	char	*ptr;

	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	z = malloc(total);
	if (z == NULL)
		return (NULL);
	ptr = z;
	while (*s1 != '\0')
	{
		*ptr = *s1;
		ptr++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*ptr = *s2;
		ptr++;
		s2++;
	}
	*ptr = '\0';
	return (z);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	substr_len;
	char	*substr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len < s_len - start)
		substr_len = len;
	else
		substr_len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (!substr)
		return (NULL);
	while (i < substr_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[substr_len] = '\0';
	return (substr);
}
