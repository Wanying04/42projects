/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:00:27 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 19:06:52 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 清理环境并退出程序
// 退出 shell 前的清理流程：
// 1. 打印 exit
// 2. 清空 readline 历史
// 3. 释放环境变量内存
int	cleanup_and_exit(t_env *env)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	env_destroy(env);
	return (1);
}

// 判断输入字符串是否全为空白字符（空格或 tab）
// 检查 str 是否全为空白字符，遇到非空白立即返回 0
int	is_empty_input(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

// 判断路径是否为目录，stat 失败或路径为空都视为否
int	is_a_directory(const char *path)
{
	struct stat	path_stat;

	if (!path)
		return (0);
	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

// 判断字符串是否为整数：
// 1. 支持 $ 前缀（如 $1）
// 2. 支持正负号
// 3. 只要有非数字字符即返回 0
int	is_integer(char *str)
{
	int	i;

	if (*str == '$')
		str++;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
