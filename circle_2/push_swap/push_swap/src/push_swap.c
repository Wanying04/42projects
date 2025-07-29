/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:15:31 by wtang             #+#    #+#             */
/*   Updated: 2025/07/28 13:06:11 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_is_sorted(t_stack *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	ft_sort_2(t_stack **stack)
{
	if (!stack || !*stack || !(*stack)->next)
		return ;
	if ((*stack)->value > (*stack)->next->value)
		sa(stack);
}

void	ft_sort_3(t_stack **stack_a)
{
	if (!stack_a || !*stack_a || !(*stack_a)->next || !(*stack_a)->next->next)
		return ;
	if ((*stack_a)->value > (*stack_a)->next->value
		&& (*stack_a)->value > (*stack_a)->next->next->value)
		ra(stack_a);
	else if ((*stack_a)->next->value > (*stack_a)->value
		&& (*stack_a)->next->value > (*stack_a)->next->next->value)
		rra(stack_a);
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a);
}

void	ft_sort_more(t_stack **a, t_stack **b)
{
	int	size;
	int	managed;

	size = stack_size(*a);
	managed = 0;
	if (!a || !*a)
		return ;
	while (managed < size && *a)
	{
		if ((*a)->index <= size / 2)
			pb(a, b);
		else
			ra(a);
		managed++;
	}
	while (stack_size(*a) > 3 && *a)
		pb(a, b);
	ft_sort_3(a);
	while (*b)
	{
		find_optimal_push(a, b);
		pa(a, b);
	}
	final_rotate(a);
}

void	push_swap(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	if (!stack_a || !*stack_a)
		return ;
	size = stack_size(*stack_a);
	if (size <= 1 || ft_is_sorted(*stack_a))
		return ;
	if (size == 2)
		ft_sort_2(stack_a);
	else if (size == 3)
		ft_sort_3(stack_a);
	else
		ft_sort_more(stack_a, stack_b);
}
