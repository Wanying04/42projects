/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:56:39 by wtang             #+#    #+#             */
/*   Updated: 2025/07/23 22:05:46 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

//DEBUG
#include <stdio.h>

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

void	sa(t_stack **stack_a);
void	sb(t_stack **stack_b);
void	pa(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void	rra(t_stack **stack_a);
void	rrb(t_stack **stack_b);
int	ft_parse_arguments(int ac, char **av, t_stack **stack);
int	ft_is_valid_int(char *s);
int	ft_has_duplicates(int *nums, int size);
t_stack *ft_create_stack(int *nums, int size);
int ft_stack_push(t_stack **stack, int value);
void ft_free_stack(t_stack **stack);
void	ft_assign_index(t_stack **stack_a);
int stack_size(t_stack *stack);
void	ft_sort_array(int *arr, int size);
void push_swap(t_stack **stack_a, t_stack **stack_b);
int	ft_is_sorted(t_stack *stack_a);
void ft_sort_2(t_stack **stack_a);
void ft_sort_3(t_stack **stack_a);
void ft_sort_more(t_stack **a, t_stack **b);
t_stack *ft_stack_last(t_stack *stack);
t_stack *ft_stack_new(int value);
int get_current_pos(t_stack *stack, t_stack *node);
int find_target_pos(t_stack *a, int value);
int find_min_position(t_stack *a);
int calculate_rotation_cost(int pos, int stack_size);
int ft_min(int a, int b);
int calculate_push_cost(int pos_a, int pos_b);
void copy_stack_to_array(t_stack *stack, int *arr);
void rr(t_stack **a, t_stack **b);
void rrr(t_stack **a, t_stack **b);
void final_rotate(t_stack **a);
int find_min_position(t_stack *a);
void find_optimal_push(t_stack **a, t_stack **b);
int find_target_pos(t_stack *a, int value);
void execute_dual_rotation(t_stack **a, t_stack **b, int rotate_a, int rotate_b);
int find_median(t_stack *s, int chunk_size);
void ft_sort_int_array(int *arr, int size);

#endif