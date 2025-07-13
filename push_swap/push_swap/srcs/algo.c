/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:15:31 by wtang             #+#    #+#             */
/*   Updated: 2025/07/13 14:13:16 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_is_sorted(t_stack *stack_a)          //to verify if stack a is already sorted
{
	while (stack_a->next != NULL)
	{
		if (stack_a->value > stack_a->next->value)
			return (0);
		stack_a = stack_a->next;
	}
	return (1);
}

void	ft_sort_2(t_stack *stack_a)         //sort 2 elements
{
	int	temp;
	
	if (stack_a->value > stack_a->next->value)
	{
		temp = stack_a->value;
		stack_a->value = stack_a->next->value;
		stack_a->next->value = temp;
		write(1, "sa", 2);	
	}
	write(1, "\n", 1);
}

void	ft_sort_3(t_stack *stack_a)         //sort 3 elements
{
	
}

void	push_swap(t_stack **stack_a, t_stack **stack_b)
{
	
}