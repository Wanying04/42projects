/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:04:10 by wtang             #+#    #+#             */
/*   Updated: 2025/07/24 16:04:53 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void final_rotate(t_stack **a)
{
    if (!a || !*a) return;
    
    int min_pos = 0;
    int min_val = (*a)->value;
    t_stack *tmp = *a;
    
    // 单次遍历找到最小值和位置
    for (int i = 0; tmp; tmp = tmp->next, i++) {
        if (tmp->value < min_val) {
            min_val = tmp->value;
            min_pos = i;
        }
    }
    
    int size = stack_size(*a);
    if (min_pos <= size/2) {
        while (min_pos--) ra(a);
    } else {
        while (min_pos++ < size) rra(a);
    }
}

void execute_dual_rotation(t_stack **a, t_stack **b, int rotate_a, int rotate_b)
{
    // 同时旋转优化
    while (rotate_a > 0 && rotate_b > 0) {
        rr(a, b);
        rotate_a--;
        rotate_b--;
    }
    while (rotate_a < 0 && rotate_b < 0) {
        rrr(a, b);
        rotate_a++;
        rotate_b++;
    }
    
    // 单独处理剩余旋转
    while (rotate_a > 0) { ra(a); rotate_a--; }
    while (rotate_a < 0) { rra(a); rotate_a++; }
    while (rotate_b > 0) { rb(b); rotate_b--; }
    while (rotate_b < 0) { rrb(b); rotate_b++; }
}

int ft_max(int a, int b)
{
	return (a > b) ? a : b;
}

int ft_min(int a, int b)
{
    return (a < b) ? a : b;
}

int calculate_rotation_cost(int pos, int stack_size)
{
	return (pos <= stack_size / 2) ? pos : stack_size - pos;
}
