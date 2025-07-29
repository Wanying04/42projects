/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:56:39 by wtang             #+#    #+#             */
/*   Updated: 2025/07/28 13:53:25 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}	t_stack;

//command_push
void	pa(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
//command_reverse_rotate
void	do_rra(t_stack **stack_a);
void	rra(t_stack **stack_a);
void	do_rrb(t_stack **stack_b);
void	rrb(t_stack **stack_b);
void	rrr(t_stack **a, t_stack **b);
//command_rotate
void	do_ra(t_stack **stack_a);
void	ra(t_stack **stack_a);
void	do_rb(t_stack **stack_b);
void	rb(t_stack **stack_b);
void	rr(t_stack **a, t_stack **b);
//command_swap
void	do_sa(t_stack **stack_a);
void	sa(t_stack **stack_a);
void	do_sb(t_stack **stack_b);
void	sb(t_stack **stack_b);
void	ss(t_stack **a, t_stack **b);
//cost
int		get_rotate_a_count(t_stack *a, int value);
int		get_rotate_b_count(t_stack *b, int value);
int		calculate_push_cost(int pos_a, int pos_b);
int		find_target_pos(t_stack *a, int value);
int		calculate_rotation_cost(int pos, int stack_size);
//final_rotate
int		find_min_position(t_stack *stack);
void	final_rotate(t_stack **a);
//index
void	ft_set_indexes(t_stack **stack, int *sorted_array, int size);
void	ft_sort_array(int *arr, int size);
int		*ft_get_sorted_array(t_stack *stack, int size);
void	ft_assign_index(t_stack **stack_a);
//parse_aditional
int		ft_has_duplicates(int *nums, int size);
int		check_number_within_range(char *s, int sign);
int		handle_sign_and_initial_check(char **s, int *sign);
int		ft_is_valid_int(char *s);
//parse_arguments
int		create_stack_and_check_duplicates(int *nums, int slen, t_stack **stack);
int		parse_and_validate_args(char **s, int *nums, int slen);
int		*prepare_parsing(int ac, char **av, char ***s, int *slen);
int		ft_parse_arguments(int ac, char **av, t_stack **stack);
//push_swap
int		ft_is_sorted(t_stack *stack);
void	ft_sort_2(t_stack **stack);
void	ft_sort_3(t_stack **stack_a);
void	ft_sort_more(t_stack **a, t_stack **b);
void	push_swap(t_stack **stack_a, t_stack **stack_b);
//stack
int		stack_size(t_stack *stack);
void	ft_free_stack(t_stack **stack);
int		ft_stack_push(t_stack **stack, int value);
t_stack	*ft_create_stack(int *nums, int size);
//strategy
void	rotate_stack_a(t_stack **a, int *r_a);
void	rotate_stack_b(t_stack **b, int *r_b);
void	execute_dual_rotation(t_stack **a, t_stack **b, int r_a, int r_b);
void	evaluate_best_push(t_stack **a, t_stack **b, int *best_a, int *best_b);
void	find_optimal_push(t_stack **a, t_stack **b);
//utils
int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		get_pos_by_value(t_stack *stack, int value);
int		get_current_pos(t_stack *stack, t_stack *node);
void	find_min_max_pos(t_stack *a, int *min_v, int *max_v, int *min_pos);

#endif