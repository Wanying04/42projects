/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:40:14 by wtang             #+#    #+#             */
/*   Updated: 2025/06/19 20:28:10 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_union(char *s1, char *s2) //union is a key word, should use FT_
{
	char	seen[256];
	int	i;

	i = 0;
	while (i < 256)
	{
		seen[i] = 0;
		i++;
	}
	i = 0;
	while (s1[i])
	{
		if (!seen[(unsigned char)s1[i]]) //判断条件
		{
			write(1, &s1[i], 1);
			seen[(unsigned char)s1[i]] = 1; //set it 1
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (!seen[(unsigned char)s2[i]])
		{
			write(1, &s2[i], 1);
			seen[(unsigned char)s2[i]] = 1;
		}
		i++;
	} //too many lines!
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
		ft_union(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
