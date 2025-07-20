/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:13:41 by wtang             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:14 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int ac, char *av[])
{
    t_stack *stack_a = NULL;
    t_stack *stack_b = NULL;
    
    if (ac == 1)
        return (0);
        
    if (ft_parse_arguments(ac, av, &stack_a) != 0)
        return (1);
    
    ft_assign_index(&stack_a);
    
    if (!ft_is_sorted(stack_a))
        push_swap(&stack_a, &stack_b);
    
    ft_free_stack(&stack_a);
    ft_free_stack(&stack_b);
    return (0);
}
