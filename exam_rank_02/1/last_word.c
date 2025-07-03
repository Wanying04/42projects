/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:13:40 by wtang             #+#    #+#             */
/*   Updated: 2025/06/20 15:54:57 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	last_word(char *str)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (str[end])
		end++;
	while (--end >= 0 && (str[end] == ' ' || str[end] == '\t')) //ATTENTION: end >= 0
		;
	if (end < 0)
		return;
	start = end;
	while (start >= 0 && (str[start] != ' ' && str[start] != '\t'))
		start--;
	while (++start <= end)
		write(1, &str[start], 1);
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
		last_word(argv[1]);
	write(1, "\n", 1);
	return (0);
}
