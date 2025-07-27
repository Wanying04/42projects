/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:19:02 by wtang             #+#    #+#             */
/*   Updated: 2025/06/19 17:47:30 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	do_op(char *s1, char *s2, char *s3)
{
	int	a;
	int	b;
	char	op;

	a = atoi(s1);
	b = atoi(s3);
	op = *s2;
	if (op == '+')
		return (a + b);
	if (op == '-')
		return (a - b);
	if (op == '*')
		return (a * b);
	if (op == '/')
	{
		if (b == 0)
			return (0);
		return (a / b);
	}
	if (op == '%')
	{
		if (b == 0)
			return (0);
		return (a % b);
	}
	return (0); //attention
}

int	main(int argc, char *argv[])
{
	int	result;

	if (argc == 4)
	{
		result = do_op(argv[1], argv[2], argv[3]);
		printf("%d", result);
	}
	write(1, "\n", 1);
	return (0);
}
