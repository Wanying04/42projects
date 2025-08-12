/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:50:56 by wtang             #+#    #+#             */
/*   Updated: 2025/07/28 15:42:33 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_set_indexes(t_stack **stack, int *sorted_array, int size)
{
	t_stack	*tmp;
	int		j;

	tmp = *stack;
	while (tmp)
	{
		j = 0;
		while (j < size)
		{
			if (sorted_array[j] == tmp->value)
			{
				tmp->index = j + 1;
				break ;
			}
			j++;
		}
		tmp = tmp->next;
	}
}

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
		if (min_idx != i)
		{
			temp = arr[i];
			arr[i] = arr[min_idx];
			arr[min_idx] = temp;
		}
		i++;
	}
}

int	*ft_get_sorted_array(t_stack *stack, int size)
{
	int		*arr;
	int		i;
	t_stack	*tmp;

	arr = malloc(size * sizeof(int));
	if (!arr)
		return (NULL);
	i = 0;
	tmp = stack;
	while (i < size)
	{
		arr[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
	ft_sort_array(arr, size);
	return (arr);
}

void	ft_assign_index(t_stack **stack_a)
{
	int		size;
	int		*sorted_array;

	if (!stack_a || !*stack_a)
		return ;
	size = stack_size(*stack_a);
	sorted_array = ft_get_sorted_array(*stack_a, size);
	if (!sorted_array)
		return ;
	ft_set_indexes(stack_a, sorted_array, size);
	free(sorted_array);
}
