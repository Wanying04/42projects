/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:32:49 by wtang             #+#    #+#             */
/*   Updated: 2025/07/25 20:09:32 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_pos_by_value(t_stack *stack, int value)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->value == value)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

int	get_current_pos(t_stack *stack, t_stack *node)
{
	int	pos;

	pos = 0;
	while (stack && stack != node)
	{
		pos++;
		stack = stack->next;
	}
	if (stack)
		return (pos);
	else
		return (-1);
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

void	find_min_max_pos(t_stack *a, int *min_v, int *max_v, int *min_pos)
{
	t_stack	*tmp;
	int		i;

	tmp = a;
	i = 0;
	*min_v = INT_MAX;
	*max_v = INT_MIN;
	*min_pos = 0;
	while (tmp)
	{
		if (tmp->value < *min_v)
		{
			*min_v = tmp->value;
			*min_pos = i;
		}
		if (tmp->value > *max_v)
			*max_v = tmp->value;
		tmp = tmp->next;
		i++;
	}
}
