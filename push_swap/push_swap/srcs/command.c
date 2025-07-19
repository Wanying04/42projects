/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:13:05 by wtang             #+#    #+#             */
/*   Updated: 2025/07/19 20:54:52 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack **stack_a)
{
	t_stack	*first;
	t_stack	*second;
	
	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return;       //When the stack is empty or has only one element, no swapping is required
	first = *stack_a;
	second =first->next;
	first->next = second->next;   //swap them
	second->next = first;
	*stack_a = second;
	write(1, "sa\n", 3);
}

void	sb(t_stack **stack_b)
{
	t_stack	*first;
	t_stack	*second;
	
	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return;       //When the stack is empty or has only one element, no swapping is required
	first = *stack_b;
	second = first->next;
	first->next = second->next;   //swap them
	second->next = first;
	*stack_b = second;
	write(1, "sb\n", 3);
}

void	pa(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*top_b;

	if (*stack_b == NULL)
		return;
	top_b = *stack_b;
	*stack_b = (*stack_b)->next;
	top_b->next = *stack_a;
	*stack_a = top_b;
	write(1, "pa\n", 3);
}

void	pb(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*top_a;

	if (*stack_a == NULL)
		return;
	top_a = *stack_a;
	*stack_a = (*stack_a)->next;
	top_a->next = *stack_b;
	*stack_b = top_a;
	write(1, "pb\n", 3);
}

void	ra(t_stack **stack_a)
{
	t_stack	*top_a;
	t_stack	*last;

	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return;
	top_a = *stack_a;
	*stack_a = (*stack_a)->next;
	last = *stack_a;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = top_a;
	top_a->next = NULL;    // Must be left empty, otherwise a loop will be formed
	write(1, "ra\n", 3);
}

void	rb(t_stack **stack_b)
{
	t_stack	*top_b;
	t_stack	*last;

	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return;
	top_b = *stack_b;
	*stack_b = (*stack_b)->next;
	last = *stack_b;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = top_b;
	top_b->next = NULL;    // Must be left empty, otherwise a loop will be formed
	write(1, "rb\n", 3);
}

void	rra(t_stack **stack_a)
{
	t_stack	*last;
	t_stack	*second_last;
	
	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return;
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
	write(1, "rra\n", 4);
}

void	rrb(t_stack **stack_b)
{
	t_stack	*last;
	t_stack	*second_last;
	
	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return;
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
	write(1, "rrb\n", 4);
}
