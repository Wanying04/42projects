/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:39:56 by wtang             #+#    #+#             */
/*   Updated: 2025/07/20 21:37:05 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include "push_swap.h"

/* 检查字符串是否为纯数字（允许前导+/-）*/
int ft_is_number(char *s)
{
    if (!s || !*s) return 0;
    
    if (*s == '+' || *s == '-') {
        if (!*(s+1)) return 0; // 只有符号的情况
        s++;
    }
    
    while (*s) {
        if (!ft_isdigit(*s)) return 0;
        s++;
    }
    return 1;
}

/* 检查字符串是否在int范围内（不使用atol/strtol）*/
int ft_is_int(char *s)
{
    int sign = 1;
    long result = 0;
    
    // 处理符号
    if (*s == '-' || *s == '+') {
        if (*s == '-') sign = -1;
        s++;
    }
    
    // 空字符串或只有符号
    if (!*s) return 0;
    
    // 逐字符计算
    while (*s) 
	{
        if (result > (INT_MAX - (*s - '0')) / 10) {
            return 0; // 正溢出检查
        }
        if (sign == -1 && (-result < (INT_MIN + (*s - '0')) / 10)) {
            return 0; // 负溢出检查
        }
        
        result = result * 10 + (*s - '0');
        s++;
    }
    
    return 1;
}

/* 检查数组中是否有重复值 */
int ft_has_duplicates(int *nums, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (nums[i] == nums[j])
                return 1;
        }
    }
    return 0;
}

/* 主参数解析函数 */
int ft_parse_arguments(int ac, char **av, t_stack **stack)
{
    int *nums;
    int i;
    
    if (ac < 2) return 0; // 无参数情况
    
    nums = malloc(sizeof(int) * (ac - 1));
    if (!nums) return 1; // 内存分配失败
    
    i = 1;
    while (i < ac) {
        if (!ft_is_number(av[i]) || !ft_is_int(av[i])) {
            free(nums);
            write(2, "Error\n", 6);
            return 1;
        }
        
        // 安全转换（因为已通过ft_is_int验证）
        nums[i-1] = ft_atoi(av[i]);
        i++;
    }
    
    if (ft_has_duplicates(nums, ac - 1)) {
        free(nums);
        write(2, "Error\n", 6);
        return 1;
    }
    
    *stack = ft_create_stack(nums, ac - 1);
    free(nums);
    
    if (!*stack) {
        write(2, "Error\n", 6);
        return 1;
    }
    return 0;
}