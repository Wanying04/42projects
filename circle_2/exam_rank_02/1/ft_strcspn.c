/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:54:10 by wtang             #+#    #+#             */
/*   Updated: 2025/06/20 13:12:15 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i; //使用 size_t 代替 int
	size_t	j; //strcspn 的返回值是 size_t，所以循环变量也保持一致

	i = 0;
	while (s[i])
	{
		j = 0; //每次检查 s 的一个新字符时，都应该重新将 j 设为 0
		while (reject[j])
		{
			if (s[i] == reject[j])
			{
				return (i);
			}
			j++;
		}
		i++;
	}
	return (i);
}
