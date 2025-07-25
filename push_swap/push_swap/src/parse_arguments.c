/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:39:56 by wtang             #+#    #+#             */
/*   Updated: 2025/07/25 21:53:01 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	create_stack_and_check_duplicates(int *nums, int slen, t_stack **stack)
{
	if (ft_has_duplicates(nums, slen))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	*stack = ft_create_stack(nums, slen);
	if (!*stack)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}

int	parse_and_validate_args(char **s, int *nums, int slen)
{
	int	i;

	i = 0;
	while (i < slen)
	{
		if (!ft_is_valid_int(s[i]))
		{
			write(2, "Error\n", 6);
			return (1);
		}
		nums[i] = ft_atoi(s[i]);
		i++;
	}
	return (0);
}

int	*prepare_parsing(int ac, char **av, char ***s, int *slen)
{
	int	*nums;

	if (ac == 2)
		*s = ft_split(av[1], ' ');
	else
		*s = av + 1;
	*slen = 0;
	while ((*s)[*slen])
		(*slen)++;
	nums = malloc(sizeof(int) * (*slen));
	return (nums);
}

int	ft_parse_arguments(int ac, char **av, t_stack **stack)
{
	int		*nums;
	char	**s;
	int		slen;

	nums = prepare_parsing(ac, av, &s, &slen);
	if (!nums)
		return (1);
	if (parse_and_validate_args(s, nums, slen))
	{
		free(nums);
		return (1);
	}
	if (create_stack_and_check_duplicates(nums, slen, stack))
	{
		free(nums);
		return (1);
	}
	free(nums);
	return (0);
}
