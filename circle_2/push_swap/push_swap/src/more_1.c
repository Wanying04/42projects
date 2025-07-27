/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:05:43 by wtang             #+#    #+#             */
/*   Updated: 2025/07/25 20:58:58 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_rotate_a_count(t_stack *a, int value)
{
	int	size_a;
	int	target_pos;

	size_a = stack_size(a);
	target_pos = find_target_pos(a, value);
	if (target_pos <= size_a / 2)
		return (target_pos);
	else
		return (-(size_a - target_pos));
}

int	get_rotate_b_count(t_stack *b, int value)
{
	int	size_b;
	int	pos_b;

	size_b = stack_size(b);
	pos_b = get_pos_by_value(b, value);
	if (pos_b <= size_b / 2)
		return (pos_b);
	else
		return (-(size_b - pos_b));
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
