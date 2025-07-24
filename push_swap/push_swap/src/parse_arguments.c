/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:39:56 by wtang             #+#    #+#             */
/*   Updated: 2025/07/24 16:28:10 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int handle_sign_and_initial_check(char **s, int *sign)
{
	if (!*s || !**s)  // 如果字符串为空或NULL，返回无效
		return (0);
	if (**s == '+' || **s == '-')  // 处理符号
	{
		if (**s == '-')
			*sign = -1;
		(*s)++;
		if (!**s)  // 如果符号后面没有数字
			return (0);
	}
	return (1);
}


int check_number_within_range(char *s, int sign)
{
	long long num = 0;
	long long limit;

	while (*s)  // 遍历字符串的每个字符
	{
		if (!ft_isdigit(*s))  // 如果不是数字，返回无效
			return (0);
		limit = (sign == 1) ? INT_MAX : (long long)INT_MAX + 1;

		// 检查越界情况
		if (num > limit / 10)
			return (0);
		if (num == limit / 10 && (*s - '0') > limit % 10)
			return (0);

		num = num * 10 + (*s - '0');
		s++;
	}
	return (1);  // 如果数字验证通过，返回有效
}


int ft_is_valid_int(char *s)
{
	int sign = 1;

	// 处理符号部分
	if (!handle_sign_and_initial_check(&s, &sign))
		return (0);

	// 验证数字部分
	return (check_number_within_range(s, sign));
}


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

int parse_and_validate_args(char **s, int *nums, int slen)
{
	int i = 0;
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

int create_stack_and_check_duplicates(int *nums, int slen, t_stack **stack)
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

int	ft_parse_arguments(int ac, char **av, t_stack **stack)
{
	int		*nums;
	char	**s;
	int		slen;

	s = (ac == 2) ? ft_split(av[1], ' ') : av + 1;
	slen = 0;
	while (s[slen]) slen++;
	nums = malloc(sizeof(int) * slen);
	if (!nums) return (1);
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
