/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_reverse_rotate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:49:03 by wtang             #+#    #+#             */
/*   Updated: 2025/07/24 15:50:26 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_rra(t_stack **stack_a)
{
	t_stack	*last;
	t_stack	*second_last;

	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	second_last = NULL;
	last = *stack_a;
	while (last->next != NULL)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *stack_a;
	*stack_a = last;
}

void	rra(t_stack **stack_a)
{
	do_rra(stack_a);
	write(1, "rra\n", 4);
}

void	do_rrb(t_stack **stack_b)
{
	t_stack	*last;
	t_stack	*second_last;

	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	second_last = NULL;
	last = *stack_b;
	while (last->next != NULL)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *stack_b;
	*stack_b = last;
}

void	rrb(t_stack **stack_b)
{
	do_rrb(stack_b);
	write(1, "rrb\n", 4);
}

void	rrr(t_stack **a, t_stack **b)
{
	do_rra(a);
	do_rrb(b);
	write(1, "rrr\n", 4);
}
