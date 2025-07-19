/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:13:05 by wtang             #+#    #+#             */
/*   Updated: 2025/07/18 13:07:52 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack **a);
void	pa(t_stack **a);
void	ra(t_stack **a);
void	rra(t_stack **a);
void	sb(t_stack **b);
void	pb(t_stack **b);
void	rb(t_stack **b);
void	rrb(t_stack **b);

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
}

void	pa(t_stack **stack_a)
{
	t_stack	*new_a;
	t_stack	*join_b;
	
	join_b = *stack_a;
	*stack_a = new_a;;
}