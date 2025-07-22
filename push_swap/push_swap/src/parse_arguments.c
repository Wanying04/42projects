/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:39:56 by wtang             #+#    #+#             */
/*   Updated: 2025/07/21 17:38:29 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_is_valid_int(char *s)
{
	int	sign;
	long long	num;

	sign = 1;
	num = 0;
	if (!s || !*s)
		return 0;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
		if (!*s) 
			return (0);
	}
	while (*s)
	{
		if (!ft_isdigit(*s)) 
			return (0);
		if (sign == 1 && num > (INT_MAX - (*s - '0')) / 10) 
			return (0);
		if (sign == -1 && -num < (INT_MIN + (*s - '0')) / 10) 
			return (0);
		num = num * 10 + (*s - '0');
		s++;
	}
	return (1);
}

int	ft_has_duplicates(int *nums, int size)
{
	int i;
	int j;

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

int	ft_parse_arguments(int ac, char **av, t_stack **stack)
{
	int	*nums;
	int	i;

	nums = malloc(sizeof(int) * (ac - 1));
	if (!nums)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (!ft_is_valid_int(av[i]))
		{
			free(nums);
			write(2, "Er\n", 3);
			return (1);
		}
		nums[i-1] = ft_atoi(av[i]);
		i++;
	}
	if (ft_has_duplicates(nums, ac - 1))
	{
		free(nums);
		write(2, "Err\n", 4);
		return (1);
	}
	*stack = ft_create_stack(nums, ac - 1);
	free(nums);
	if (!*stack)
	{
		write(2, "Erro\n", 5);
		return (1);
	}
	return (0);
}
