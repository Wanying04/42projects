/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:04:10 by wtang             #+#    #+#             */
/*   Updated: 2025/07/25 21:07:12 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_position(t_stack *stack)
{
	int		min_pos;
	int		min_val;
	t_stack	*tmp;
	int		i;

	if (!stack)
		return (0);
	min_pos = 0;
	min_val = stack->value;
	tmp = stack;
	i = 0;
	while (tmp)
	{
		if (tmp->value < min_val)
		{
			min_val = tmp->value;
			min_pos = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (min_pos);
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
    while (r_a > 0)
    {
        ra(a);
        r_a--;
    }
    while (r_a < 0)
    {
        rra(a);
        r_a++;
    }
    while (r_b > 0)
    {
        rb(b);
        r_b--;
    }
    while (r_b < 0)
    {
        rrb(b);
        r_b++;
    }
}

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

int	calculate_rotation_cost(int pos, int stack_size)
{
	if (pos <= stack_size / 2)
		return (pos);
	else
		return (stack_size - pos);
}
