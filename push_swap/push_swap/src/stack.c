/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:44:25 by wtang             #+#    #+#             */
/*   Updated: 2025/07/24 16:34:35 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_size(t_stack *stack)
{
	int	count;

	count = 0;
	while (stack != NULL)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

void	ft_free_stack(t_stack **stack)
{
	t_stack	*tmp;

	while (*stack != NULL)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

int	ft_stack_push(t_stack **stack, int value)
{
	t_stack	*new_node;

	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		return (-1);
	new_node->value = value;
	new_node->next = *stack;
	*stack = new_node;
	return (0);
}

t_stack	*ft_create_stack(int *nums, int size)
{
	t_stack	*stack;
	int		i;

	stack = NULL;
	i = size - 1;
	while (i >= 0)
	{
		if (ft_stack_push(&stack, nums[i]) == -1)
		{
			ft_free_stack(&stack);
			return (NULL);
		}
		i--;
	}
	return (stack);
}
