/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:09:15 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 19:08:29 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 释放环境变量数组的内存
// free_env_array:
// 1. 释放 env_array 指向的每个字符串。
// 2. 释放 env_array 本身。
static void	free_env_array(char **env_array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

// env_to_array:
// 1. 分配 env->count+1 个指针空间。
// 2. 拷贝每个环境变量字符串。
// 3. 失败时释放所有已分配内存。
// 4. 返回 NULL 结尾的字符串数组。
// 将 t_env 结构体转换为字符串数组，供 execve 使用
char	**env_to_array(t_env *env)
{
	char	**env_array;
	int		i;

	if (!env || !env->vars)
		return (NULL);
	env_array = ft_calloc(sizeof(char *), (env->count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (i < env->count)
	{
		env_array[i] = ft_strdup(env->vars[i]);
		if (!env_array[i])
			return (free_env_array(env_array, i), NULL);
		i++;
	}
	env_array[env->count] = NULL;
	return (env_array);
}
