/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:56:20 by wtang             #+#    #+#             */
/*   Updated: 2025/07/13 16:58:02 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	min_idx;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
				j++;
		}
		temp = arr[i];
		arr[i] = arr[min_idx];
		arr[min_idx] = temp;
		i++;
	}
}

void	ft_assign_index(t_stack **stack_a)
{
	int	size;
	int	*values;
	t_stack	*tmp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	size = stack_size(*stack_a);
	if (size == 0)
		return;
	values = malloc(size * sizeof(int));
	if (!values)
		return;
	tmp = *stack_a;
	while (i < size)
	{
		values[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
	ft_sort_array(values, size);
	tmp = *stack_a;
	while (tmp)
	{
		while (j < size)
		{
			if (values[j] == tmp->value)
			{
				tmp->index = j + 1;
				break;
			}
			j++;
		}
		tmp = tmp->next;
	}
	free (values);
}

int	ft_parse_arguments(int ac, char **av, t_stack **stack)
{
	long	num;
	int	*nums;
	int	i;

	stack = NULL;
	while (i < ac)
	{
		if (!ft_is_number(av[i]) || !ft_is_int(av[i]))
		{
			free (nums);
			write(2, "Error\n", 6);
			return (1);
		}
		nums[i - 1] = ft_atoi(av[i]);
		i++;
	}
	if (ft_has_duplicates(nums, ac - 1))
	{
		free (nums);
		write(2, "Error\n", 6);
		return (1);
	}
}
