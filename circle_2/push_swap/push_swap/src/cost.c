/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:04:10 by wtang             #+#    #+#             */
/*   Updated: 2025/07/28 13:43:08 by wtang            ###   ########.fr       */
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

int	calculate_push_cost(int pos_a, int pos_b)
{
	int	cost;

	if (pos_a >= 0 && pos_b >= 0)
		cost = ft_max(pos_a, pos_b);
	else if (pos_a < 0 && pos_b < 0)
		cost = ft_max(-pos_a, -pos_b);
	else
		cost = abs(pos_a) + abs(pos_b);
	return (cost);
}

int	find_target_pos(t_stack *a, int value)
{
	int		min_value;
	int		max_value;
	int		min_pos;
	int		pos;
	t_stack	*tmp;

	if (!a || !a->next)
		return (0);
	find_min_max_pos(a, &min_value, &max_value, &min_pos);
	if (value < min_value || value > max_value)
		return (min_pos);
	tmp = a;
	pos = 0;
	while (tmp->next)
	{
		if (value > tmp->value && value < tmp->next->value)
			return (pos + 1);
		tmp = tmp->next;
		pos++;
	}
	return (0);
}

int	calculate_rotation_cost(int pos, int stack_size)
{
	if (pos <= stack_size / 2)
		return (pos);
	else
		return (stack_size - pos);
}
