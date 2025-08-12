/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_aditional.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:32:47 by wtang             #+#    #+#             */
/*   Updated: 2025/07/25 21:56:51 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_has_duplicates(int *nums, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (nums[i] == nums[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_number_within_range(char *s, int sign)
{
	long long	num;
	long long	limit;

	num = 0;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		if (sign == 1)
			limit = INT_MAX;
		else
			limit = (long long)INT_MAX + 1;
		if (num > limit / 10)
			return (0);
		if (num == limit / 10 && (*s - '0') > limit % 10)
			return (0);
		num = num * 10 + (*s - '0');
		s++;
	}
	return (1);
}

int	handle_sign_and_initial_check(char **s, int *sign)
{
	if (!*s || !**s)
		return (0);
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			*sign = -1;
		(*s)++;
		if (!**s)
			return (0);
	}
	return (1);
}

int	ft_is_valid_int(char *s)
{
	int	sign;

	sign = 1;
	if (!handle_sign_and_initial_check(&s, &sign))
		return (0);
	return (check_number_within_range(s, sign));
}
