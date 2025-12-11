/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:08:53 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:44:24 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================
// 环境变量结构体管理主流程
// =============================
// 创建并初始化环境变量结构体，将 envp 数组内容导入 t_env
// env_create:
// 1. 分配 t_env 结构体及其成员内存。
// 2. 初始化容量、计数、状态等。
// 3. 遍历 envp，将每个环境变量导入 t_env。
t_env	*env_create(char **envp)
{
	t_env	*env;
	int		i;

	env = ft_calloc(sizeof(t_env), 1);
	env->capacity = 100;
	env->count = 0;
	env->exit_status = SUCCESS;
	env->vars = ft_calloc(sizeof(char *), env->capacity);
	env->vars[0] = NULL;
	env->pwd = ft_calloc(sizeof(t_pwd), 1);
	env->pwd->pwd = NULL;
	env->pwd->oldpwd = NULL;
	if (!envp)
		return (env);
	i = 0;
	while (envp[i])
	{
		env_set(env, envp[i]);
		i++;
	}
	return (env);
}

// env_destroy:
// 1. 释放所有环境变量字符串。
// 2. 释放 pwd 结构体及其成员。
// 3. 释放 t_env 本身。
// 释放 t_env 结构体及其所有分配的内存
void	env_destroy(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		free(env->vars[i]);
		i++;
	}
	free(env->vars);
	if (env->pwd)
	{
		if (env->pwd->pwd)
			free(env->pwd->pwd);
		if (env->pwd->oldpwd)
			free(env->pwd->oldpwd);
		free(env->pwd);
	}
	free(env);
}

// env_expand:
// 1. 动态扩容 vars 数组，容量翻倍。
// 2. 拷贝原有指针，释放旧数组。
// 扩展环境变量数组的容量（动态扩容）
void	env_expand(t_env *env)
{
	int		new_capacity;
	char	**new_vars;
	int		i;

	new_capacity = env->capacity * 2;
	new_vars = ft_calloc(sizeof(char *), new_capacity);
	i = 0;
	while (i < env->count)
	{
		new_vars[i] = env->vars[i];
		i++;
	}
	free(env->vars);
	env->vars = new_vars;
	env->capacity = new_capacity;
}
