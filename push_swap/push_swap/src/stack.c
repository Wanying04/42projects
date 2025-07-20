/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:44:25 by wtang             #+#    #+#             */
/*   Updated: 2025/07/20 19:46:04 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void ft_free_stack(t_stack **stack)
{
    t_stack *tmp;

    while (*stack != NULL)
    {
        tmp = (*stack)->next;  // 保存下一个节点
        free(*stack);           // 释放当前节点
        *stack = tmp;           // 移动指针
    }
}

int ft_stack_push(t_stack **stack, int value)
{
    t_stack *new_node;

    new_node = malloc(sizeof(t_stack));
    if (!new_node)          // 内存分配失败
        return (-1);
    
    new_node->value = value;
    new_node->next = *stack;  // 新节点指向原栈顶
    *stack = new_node;        // 更新栈顶指针
    return (0);               // 成功
}

t_stack *ft_create_stack(int *nums, int size)
{
    t_stack *stack = NULL;  // 初始化空栈
    int     i = 0;

    // 逆序插入（因为栈是LIFO，但根据项目需求可能需要调整）
    while (i < size)
    {
        if (ft_stack_push(&stack, nums[i]) == -1)  // 插入失败
        {
            ft_free_stack(&stack);  // 释放已分配的内存
            return (NULL);
        }
        i++;
    }
    return (stack);  // 返回栈顶指针
}
