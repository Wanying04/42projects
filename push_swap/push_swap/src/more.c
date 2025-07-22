/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:05:43 by wtang             #+#    #+#             */
/*   Updated: 2025/07/22 20:23:54 by wtang            ###   ########.fr       */
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
    if (!a)
        return 0;

    t_stack *tmp = a;
    int pos = 0;
 

    // 先找最小和最大值及其位置
    int min_value = tmp->value;
    int max_value = tmp->value;
    int min_pos = 0;
    int i = 0;
    for (t_stack *cur = a; cur; cur = cur->next, i++) {
        if (cur->value < min_value) {
            min_value = cur->value;
            min_pos = i;
        }
        if (cur->value > max_value) {
            max_value = cur->value;
        }
    }

    // 如果 value 小于最小值 或 大于最大值，目标是最小值的位置（插入前面）
    if (value < min_value || value > max_value)
        return min_pos;

    // 否则，找到第一个 tmp 和 tmp->next，满足 value > tmp->value && value < tmp->next->value
    tmp = a;
    pos = 0;
    while (tmp->next)
    {
        if (value > tmp->value && value < tmp->next->value)
            return pos + 1;
        tmp = tmp->next;
        pos++;
    }

    // 如果没找到，返回0（栈顶部）
    return 0;
}


int calculate_rotation_cost(int pos, int stack_size)
{
    return (pos <= stack_size / 2) ? pos : stack_size - pos;
}

int ft_min(int a, int b)
{
    return (a < b) ? a : b;
}

int ft_max(int a, int b)
{
    return (a > b) ? a : b;
}


int calculate_push_cost(t_stack *a, t_stack *b, t_stack *node, int target_pos)
{
    int size_a = stack_size(a);
    int size_b = stack_size(b);
    int pos_b = get_current_pos(b, node);

    int cost_a = calculate_rotation_cost(target_pos, size_a);
    int cost_b = calculate_rotation_cost(pos_b, size_b);

    if ((cost_a > 0 && cost_b > 0) || (cost_a < 0 && cost_b < 0))
        return ft_max(abs(cost_a), abs(cost_b));
    else
        return abs(cost_a) + abs(cost_b);
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
    while (rotate_a > 0) {
    	ra(a);
    	rotate_a--;
	}
	while (rotate_a < 0) {
   		rra(a);
    	rotate_a++;
	}
	while (rotate_b > 0) {
  	  rb(b);
  	  rotate_b--;
	}
	while (rotate_b < 0) {
  	  rrb(b);
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
            int pos_b = get_current_pos(*b, current);
			best_rotate_b = (pos_b <= stack_size(*b)/2) ? pos_b : pos_b - stack_size(*b);
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

void push_chunks_to_b(t_stack **a, t_stack **b, int chunks)
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
        if (min_pos <= size / 2)
		{
  		  while (min_pos-- > 0)
        	ra(a);
		}
		else
		{
    		int rotate = size - min_pos;
   	 		while (rotate-- > 0)
        		rra(a);
		}
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