/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:46:40 by wtang             #+#    #+#             */
/*   Updated: 2025/07/24 15:47:59 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_ra(t_stack **stack_a)
{
	t_stack	*top_a;
	t_stack	*last;

	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	top_a = *stack_a;
	*stack_a = (*stack_a)->next;
	last = *stack_a;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = top_a;
	top_a->next = NULL;
}

void	ra(t_stack **stack_a)
{
	do_ra(stack_a);
	write(1, "ra\n", 3);
}

void	do_rb(t_stack **stack_b)
{
	t_stack	*top_b;
	t_stack	*last;

	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	top_b = *stack_b;
	*stack_b = (*stack_b)->next;
	last = *stack_b;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = top_b;
	top_b->next = NULL;
}

void	rb(t_stack **stack_b)
{
	do_rb(stack_b);
	write(1, "rb\n", 3);
}

void	rr(t_stack **a, t_stack **b)
{
	do_ra(a);
	do_rb(b);
	write(1, "rr\n", 3);
}
