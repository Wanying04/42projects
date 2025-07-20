/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:05:43 by wtang             #+#    #+#             */
/*   Updated: 2025/07/20 21:19:31 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack *ft_stack_last(t_stack *stack)
{
    if (!stack) return NULL;
    while (stack->next)
        stack = stack->next;
    return stack;
}

t_stack *ft_stack_new(int value)
{
    t_stack *new = malloc(sizeof(t_stack));
    if (!new) return NULL;
    new->value = value;
    new->next = NULL;
    return new;
}

int get_current_pos(t_stack *stack, t_stack *node)
{
    int pos = 0;
    while (stack && stack != node) {
        pos++;
        stack = stack->next;
    }
    return stack ? pos : -1;
}

int find_target_pos(t_stack *a, int value)
{
    int pos = 0;
    t_stack *tmp = a;
    
    while (tmp->next && !(value > tmp->value && value < tmp->next->value)) {
        pos++;
        tmp = tmp->next;
    }
    return (tmp->next) ? pos + 1 : 0;
}

int calculate_rotation_cost(int pos, int stack_size)
{
    return (pos <= stack_size / 2) ? pos : stack_size - pos;
}

int ft_min(int a, int b)
{
    return (a < b) ? a : b;
}

int calculate_push_cost(t_stack *a, t_stack *b, t_stack *node, int target_pos)
{
    int cost_a = calculate_rotation_cost(target_pos, stack_size(a));
    int cost_b = calculate_rotation_cost(get_current_pos(b, node), stack_size(b));
    return cost_a + cost_b - ft_min(cost_a, cost_b);
}

void copy_stack_to_array(t_stack *stack, int *arr)
{
    int i = 0;
    while (stack) {
        arr[i++] = stack->value;
        stack = stack->next;
    }
}

void rr(t_stack **a, t_stack **b) {
    ra(a);
    rb(b);
    write(1, "rr\n", 3);
}

void rrr(t_stack **a, t_stack **b) {
    rra(a);
    rrb(b);
    write(1, "rrr\n", 4);
}

void execute_dual_rotation(t_stack **a, t_stack **b, int rotate_a, int rotate_b)
{
    while (rotate_a > 0 && rotate_b > 0) {
        rr(a, b);
        rotate_a--;
        rotate_b--;
    }
    while (rotate_a < 0 && rotate_b < 0) {
        rrr(a, b);
        rotate_a++;
        rotate_b++;
    }
    while (rotate_a-- > 0) ra(a);
    while (rotate_a++ < 0) rra(a);
    while (rotate_b-- > 0) rb(b);
    while (rotate_b++ < 0) rrb(b);
}

void find_optimal_push(t_stack **a, t_stack **b)
{
    t_stack *current = *b;
    int min_cost = INT_MAX;
    int best_rotate_a = 0;
    int best_rotate_b = 0;
    
    while (current)
    {
        int target_pos = find_target_pos(*a, current->value);
        int cost = calculate_push_cost(*a, *b, current, target_pos);
        
        if (cost < min_cost) {
            min_cost = cost;
            best_rotate_a = (target_pos <= stack_size(*a)/2) ? target_pos : target_pos - stack_size(*a);
            best_rotate_b = get_current_pos(*b, current);
        }
        current = current->next;
    }
    execute_dual_rotation(a, b, best_rotate_a, best_rotate_b);
}

int find_median(t_stack *s, int chunk_size)
{
    int *arr = malloc(chunk_size * sizeof(int));
    if (!arr) return 0;
    
    t_stack *tmp = s;
    for (int i = 0; i < chunk_size && tmp; i++) {
        arr[i] = tmp->value;
        tmp = tmp->next;
    }
    
    ft_sort_int_array(arr, chunk_size);
    int median = arr[chunk_size / 2];
    free(arr);
    return median;
}

void ft_sort_int_array(int *arr, int size)
{
    if (size <= 1) return;
    
    int pivot = arr[size / 2];
    int i = 0, j = size - 1;
    
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            int tmp = arr[i];
            arr[i++] = arr[j];
            arr[j--] = tmp;
        }
    }
    ft_sort_int_array(arr, j + 1);
    ft_sort_int_array(arr + i, size - i);
}

static void push_chunks_to_b(t_stack **a, t_stack **b, int chunks)
{
    int size = stack_size(*a);
    int items_per_chunk = size / chunks;
    int remaining = size - (items_per_chunk * chunks);
    
    while (chunks-- > 0)
    {
        int current_chunk_size = items_per_chunk + (remaining-- > 0 ? 1 : 0);
        int median = find_median(*a, current_chunk_size);
        int pushed = 0;
        
        while (pushed < current_chunk_size && *a)
        {
            if ((*a)->value <= median) {
                pb(a, b);
                pushed++;
            }
            else
                ra(a);
        }
    }
}

void final_rotate(t_stack **a)
{
    int min_pos = find_min_position(*a);
    int size = stack_size(*a);
    
    if (min_pos <= size/2)
        while (min_pos--) ra(a);
    else
        while (min_pos++ < size) rra(a);
}

int find_min_position(t_stack *a)
{
    int min_val = INT_MAX;
    int pos = 0;
    int min_pos = 0;
    
    while (a) {
        if (a->value < min_val) {
            min_val = a->value;
            min_pos = pos;
        }
        pos++;
        a = a->next;
    }
    return min_pos;
}

void ft_sort_more(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);
    int chunks = (size > 100) ? 5 : 3;
    
    push_chunks_to_b(a, b, chunks);
    if (!ft_is_sorted(*a))
        ft_sort_3(a);
    while (*b) {
        find_optimal_push(a, b);
        pa(a, b);
    }
    final_rotate(a);
}
