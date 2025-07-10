/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:56:20 by wtang             #+#    #+#             */
/*   Updated: 2025/07/10 17:48:02 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	min_idx;

	i = 0;
	while (i < size - 1)
	{
		min_idx = i;
		while (j < size)
		{
			j = i + 1;
			if (arr[j] < arr[min_idx])
				min_idx = j;
				j++;
		}
	}
}

void	assign_index(t_stack **stack_a)
{
	int	size;
	int	*values;
	t_stack	*tmp;
	int	i;

	i = 0;
	size = stack_size(*stack_a);
	if (size == 0)
		return;
	values = malloc(size * sizeof(int));
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
		while (i < size)
		{
			if (values[i] == tmp->value)
			{
				tmp->index = i + 1;
				break;
			}
		}
		tmp = tmp->next;
	}
	free (values);
}

void	push_swap(int *stack_a, int *stack_b)
{

}

t_stack parse_arguments(int ac, char **av)
{
	t_stack	*stack;
	long	num;
	int	*nums;

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

int	main(int ac, char *av[])
{
	int	i;
	int	*nums;
	t_stack	*stack_a;
	t_stack	*stack_b;

	i = 1;
	stack_a = NULL;
	stack_a = NULL;
	if (ac == 1)
		return (0);
	nums = malloc((ac - 1) * sizeof(int));
	if (!nums)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	
	stack_a = parse_arguments(ac, av);
	if (!stack_a)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (!is_sorted(stack_a))
	{
		push_swap(&stack_a, &stack_b);
	}
	free (&stack_a);
	free (&stack_b);
	free (nums);
	return (0);
}
