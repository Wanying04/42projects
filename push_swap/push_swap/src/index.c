/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:50:56 by wtang             #+#    #+#             */
/*   Updated: 2025/07/20 20:58:58 by wtang            ###   ########.fr       */
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

// 计算栈中元素的数量
int stack_size(t_stack *stack)
{
    int count = 0;
    
    while (stack != NULL)
    {
        count++;
        stack = stack->next;
    }
    return (count);
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
	if (!stack_a || !*stack_a)
		return;
	size = stack_size(*stack_a);
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
		j = 0;
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
