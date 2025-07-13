/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:13:05 by wtang             #+#    #+#             */
/*   Updated: 2025/07/13 17:13:40 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sa(t_stack **a);
void	pa(t_stack **a);
void	ra(t_stack **a);
void	rra(t_stack **a);
void	sb(t_stack **b);
void	pb(t_stack **b);
void	rb(t_stack **b);
void	rrb(t_stack **b);

void sa(t_stack **stack_a)
{
    t_stack *first;
    t_stack *second;
    
    if (*stack_a == NULL || (*stack_a)->next == NULL)
        return;  // 栈为空或只有一个元素时不需要交换
    
    first = *stack_a;
    second = first->next;
    
    // 执行交换
    first->next = second->next;
    second->next = first;
    *stack_a = second;
}