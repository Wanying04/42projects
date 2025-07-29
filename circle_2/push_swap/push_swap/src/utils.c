/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:32:49 by wtang             #+#    #+#             */
/*   Updated: 2025/07/28 13:39:11 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

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
