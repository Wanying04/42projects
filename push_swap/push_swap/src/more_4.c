/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:03:52 by wtang             #+#    #+#             */
/*   Updated: 2025/07/25 20:04:27 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	final_rotate(t_stack **a)
{
	int		min_pos;
	int		size;

	if (!a || !*a)
		return ;
	size = stack_size(*a);
	min_pos = find_min_position(*a);
	if (min_pos <= size / 2)
	{
		while (min_pos-- > 0)
			ra(a);
	}
	else
	{
		while (min_pos++ < size)
			rra(a);
	}
}
