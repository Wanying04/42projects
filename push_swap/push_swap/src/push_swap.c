/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:15:31 by wtang             #+#    #+#             */
/*   Updated: 2025/07/20 21:21:07 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int ft_is_sorted(t_stack *stack_a)
{
    if (!stack_a)
        return (1);
    while (stack_a->next != NULL)
    {
        if (stack_a->value > stack_a->next->value)
            return (0);
        stack_a = stack_a->next;
    }
    return (1);
}

void ft_sort_2(t_stack **stack_a)
{
    if (!stack_a || !*stack_a || !(*stack_a)->next)
        return;
    
    if ((*stack_a)->value > (*stack_a)->next->value)
        sa(stack_a);
}

void ft_sort_3(t_stack **stack_a)
{
    if (!stack_a || !*stack_a) return;
    
    int top = (*stack_a)->value;
    int mid = (*stack_a)->next->value;
    int bot = (*stack_a)->next->next->value;

    if (top > mid && mid < bot && top < bot)
        sa(stack_a);
    else if (top > mid && mid > bot)
    {
        sa(stack_a);
        rra(stack_a);
    }
    else if (top > mid && mid < bot)
        ra(stack_a);
    else if (top < mid && mid > bot && top < bot)
    {
        sa(stack_a);
        ra(stack_a);
    }
    else if (top < mid && mid > bot)
        rra(stack_a);
}

void push_swap(t_stack **stack_a, t_stack **stack_b)
{
    int size = stack_size(*stack_a);
    
    if (ft_is_sorted(*stack_a))
        return;
    
    if (size == 2)
        ft_sort_2(stack_a);  // 修改为传递二级指针
    else if (size == 3)
        ft_sort_3(stack_a);
    else
        ft_sort_more(stack_a, stack_b);
}
