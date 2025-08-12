/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzbuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:20:59 by wtang             #+#    #+#             */
/*   Updated: 2025/06/09 12:47:44 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	convert(int num)
{
	char	c;

	if (num >= 10)
	{
		c = num / 10 + '0';
		write(1, &c, 1);
		c = num % 10 + '0';
		write(1, &c, 1);
	}
	else
	{
		c = num + '0';
		write(1, &c, 1);
	}
	write(1, "\n", 1);
}

void	fizzbuzz(void)
{
	int	num;

	num = 1;
	while (num <= 100)
	{
		if (num % 3 == 0 && num % 5 == 0)
			write(1, "fizzbuzz\n", 9);
		else if (num % 3 == 0)
			write(1, "fizz\n", 5);
		else if (num % 5 == 0)
			write(1, "buzz\n", 5);
		else
			convert(num);
		num++;
	}
}

int	main(void)
{
	fizzbuzz();
	return (0);
}
