/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:05:43 by wtang             #+#    #+#             */
/*   Updated: 2025/07/24 16:22:01 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int find_target_pos(t_stack *a, int value)
{
	int min_value, max_value, min_pos;

	if (!a || !a->next)
		return 0;

	// 找到最小值、最大值及其位置
	find_min_max_pos(a, &min_value, &max_value, &min_pos);

	// 如果目标值超出了栈的最小值或最大值范围，直接返回最小值位置
	if (value < min_value || value > max_value)
		return min_pos;

	// 进行第二次遍历，找出目标值应该插入的位置
	t_stack *tmp = a;
	int pos = 0;
	while (tmp->next)
	{
		if (value > tmp->value && value < tmp->next->value)
			return (pos + 1);
		tmp = tmp->next;
		pos++;
	}
	return 0;
}

void find_min_max_pos(t_stack *a, int *min_value, int *max_value, int *min_pos)
{
	t_stack *tmp = a;
	int i = 0;

	*min_value = INT_MAX;
	*max_value = INT_MIN;
	*min_pos = 0;

	while (tmp)
	{
		if (tmp->value < *min_value)
		{
			*min_value = tmp->value;
			*min_pos = i;
		}
		if (tmp->value > *max_value)
			*max_value = tmp->value;
		tmp = tmp->next;
		i++;
	}
}


int get_pos_by_value(t_stack *stack, int value)
{
	int pos = 0;

	while (stack)
	{
		if (stack->value == value)
			return pos;
		pos++;
		stack = stack->next;
	}
	return -1; // 如果没找到，返回 -1
}

int get_push_cost(t_stack *a, t_stack *b, int value, int *rotate_a, int *rotate_b)
{
	int size_a = stack_size(a);
	int size_b = stack_size(b);
	int target_pos = find_target_pos(a, value);
	int pos_b = get_pos_by_value(b, value);

	*rotate_a = (target_pos <= size_a / 2) ? target_pos : -(size_a - target_pos);
	*rotate_b = (pos_b <= size_b / 2) ? pos_b : -(size_b - pos_b);

	return calculate_push_cost(*rotate_a, *rotate_b);
}

void evaluate_best_push(t_stack **a, t_stack **b, int *best_a, int *best_b)
{
	t_stack *curr = *b;
	int min_cost = INT_MAX;

	while (curr)
	{
		int rotate_a, rotate_b;
		int cost = get_push_cost(*a, *b, curr->value, &rotate_a, &rotate_b);

		if (cost < min_cost)
		{
			min_cost = cost;
			*best_a = rotate_a;
			*best_b = rotate_b;
		}
		curr = curr->next;
	}
}

void find_optimal_push(t_stack **a, t_stack **b)
{
	int best_rotate_a = 0;
	int best_rotate_b = 0;

	evaluate_best_push(a, b, &best_rotate_a, &best_rotate_b);
	execute_dual_rotation(a, b, best_rotate_a, best_rotate_b);
}

void	ft_sort_more(t_stack **a, t_stack **b)
{
	int	size;
	int	managed;

	size = stack_size(*a);
	managed = 0;
	if (!a || !*a)
		return ;
	while (managed < size && *a)
	{
		if ((*a)->index <= size / 2)
			pb(a, b);
		else
			ra(a);
		managed++;
	}
	while (stack_size(*a) > 3 && *a)
		pb(a, b);
	ft_sort_3(a);
	while (*b)
	{
		find_optimal_push(a, b);
		pa(a, b);
	}
	final_rotate(a);
}
