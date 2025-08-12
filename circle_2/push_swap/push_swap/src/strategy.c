/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:05:43 by wtang             #+#    #+#             */
/*   Updated: 2025/07/28 13:41:33 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_stack_a(t_stack **a, int *r_a)
{
	while (*r_a > 0)
	{
		ra(a);
		(*r_a)--;
	}
	while (*r_a < 0)
	{
		rra(a);
		(*r_a)++;
	}
}

void	rotate_stack_b(t_stack **b, int *r_b)
{
	while (*r_b > 0)
	{
		rb(b);
		(*r_b)--;
	}
	while (*r_b < 0)
	{
		rrb(b);
		(*r_b)++;
	}
}

void	execute_dual_rotation(t_stack **a, t_stack **b, int r_a, int r_b)
{
	while (r_a > 0 && r_b > 0)
	{
		rr(a, b);
		r_a--;
		r_b--;
	}
	while (r_a < 0 && r_b < 0)
	{
		rrr(a, b);
		r_a++;
		r_b++;
	}
	rotate_stack_a(a, &r_a);
	rotate_stack_b(b, &r_b);
}

void	evaluate_best_push(t_stack **a, t_stack **b, int *best_a, int *best_b)
{
	t_stack	*curr;
	int		min_cost;
	int		rotate_a;
	int		rotate_b;
	int		cost;

	curr = *b;
	min_cost = INT_MAX;
	while (curr)
	{
		rotate_a = get_rotate_a_count(*a, curr->value);
		rotate_b = get_rotate_b_count(*b, curr->value);
		cost = calculate_push_cost(rotate_a, rotate_b);
		if (cost < min_cost)
		{
			min_cost = cost;
			*best_a = rotate_a;
			*best_b = rotate_b;
		}
		curr = curr->next;
	}
}

void	find_optimal_push(t_stack **a, t_stack **b)
{
	int	best_rotate_a;
	int	best_rotate_b;

	best_rotate_a = 0;
	best_rotate_b = 0;
	evaluate_best_push(a, b, &best_rotate_a, &best_rotate_b);
	execute_dual_rotation(a, b, best_rotate_a, best_rotate_b);
}
