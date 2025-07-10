/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:56:39 by wtang             #+#    #+#             */
/*   Updated: 2025/07/10 17:52:14 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

typedef struct s_stack
{
	int	value;                 //int to sort
	int	index;                 //corresponding index
	int	pos;                   //position in the current stack
	int	target_pos;            //for element in b, target position in a
	int	cost_a;                //actions to make element to the top of a
	int	cost_b;                //actions to make element to the top of b
	struct s_stack	*next;
} t_stack;

void	sa(t_stack **a);
void	pa(t_stack **a);
void	ra(t_stack **a);
void	rra(t_stack **a);
void	sb(t_stack **b);
void	pb(t_stack **b);
void	rb(t_stack **b);
void	rrb(t_stack **b);

#endif