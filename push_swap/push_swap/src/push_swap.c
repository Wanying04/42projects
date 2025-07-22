/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:15:31 by wtang             #+#    #+#             */
/*   Updated: 2025/07/22 19:43:37 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int ft_is_sorted(t_stack *stack)
{
    if (!stack)
        return 1;
    while (stack->next)
    {
        if (stack->value > stack->next->value)
            return 0;
        stack = stack->next;
    }
    return 1;
}

void ft_sort_2(t_stack **stack)
{
    if (!stack || !*stack || !(*stack)->next)
        return;
    if ((*stack)->value > (*stack)->next->value)
        sa(stack);
}

void ft_sort_3(t_stack **stack_a)
{
    if (!stack_a || !*stack_a || !(*stack_a)->next || !(*stack_a)->next->next)
        return;

    int top = (*stack_a)->value;
    int mid = (*stack_a)->next->value;
    int bot = (*stack_a)->next->next->value;

    if (top < mid && mid < bot)       // 1 2 3 → 已排序
        return;
    else if (top > mid && mid < bot && top < bot)  // 2 1 3 → sa → 1 2 3
        sa(stack_a);
    else if (top > mid && mid > bot)   // 3 2 1 → sa + rra → 2 1 3 → sa → 1 2 3
    {
        sa(stack_a);
        rra(stack_a);
    }
    else if (top > mid && mid < bot)   // 3 1 2 → ra → 1 2 3
        ra(stack_a);
    else if (top < mid && mid > bot && top < bot)  // 1 3 2 → rra → 2 1 3 → sa → 1 2 3
    {
        rra(stack_a);
        sa(stack_a);
    }
    else if (top < mid && mid > bot)   // 2 3 1 → rra → 1 2 3
        rra(stack_a);
}

void push_swap(t_stack **stack_a, t_stack **stack_b)
{
    if (!stack_a || !*stack_a)
        return;
    
    int size = stack_size(*stack_a);
    if (size <= 1 || ft_is_sorted(*stack_a))
        return;
    
    if (size == 2)
        ft_sort_2(stack_a);
    else if (size == 3)
        ft_sort_3(stack_a);
    else
        ft_sort_more(stack_a, stack_b);
}
