/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:13:41 by wtang             #+#    #+#             */
/*   Updated: 2025/07/13 17:04:00 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char *av[])
{
	int	*nums;
	t_stack	*stack_a;
	t_stack	*stack_b;

	nums = NULL;
	stack_a = NULL;
	stack_a = NULL;
	if (ac == 1)
		return (0);
	if (ft_parse_arguments(ac, av, &stack_a) != 0)
	{
		ft_free_stack(&stack_a);
		write(2, "Error\n", 6);
		return (1);
	}
	if (!is_sorted(stack_a))
		push_swap(&stack_a, &stack_b);
	ft_free_stack (&stack_a);
	ft_free_stack (&stack_b);
	if (nums)
		free (nums);
	return (0);
}

void	ft_free_stack(t_stack **stack)
{
	t_stack *tmp;
	
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}
