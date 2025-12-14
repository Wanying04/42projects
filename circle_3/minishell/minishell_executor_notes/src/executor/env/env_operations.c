/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:10:09 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 19:08:22 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 如果变量已存在则更新，否则返回 FAILURE
// update_if_exists:
// 1. 遍历 vars，查找同名变量。
// 2. 找到则释放原有字符串并替换，返回 SUCCESS。
// 3. 未找到返回 FAILURE。
static int	update_if_exists(t_env *env, char *new_var, int name_len)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		if (ft_strncmp(env->vars[i], new_var, name_len) == 0
			&& (env->vars[i][name_len] == '='
			|| env->vars[i][name_len] == '\0'))
		{
			free(env->vars[i]);
			env->vars[i] = new_var;
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

// env_set:
// 1. 拷贝 var_str，分离变量名。
// 2. 若已存在则更新，否则扩容并追加。
// 3. 保证 vars 以 NULL 结尾。
// 设置或更新环境变量
void	env_set(t_env *env, const char *var_str)
{
	char	*new_var;
	char	*equal_sign;
	int		name_len;

	new_var = ft_strdup(var_str);
	equal_sign = ft_strchr(new_var, '=');
	if (equal_sign)
		name_len = equal_sign - new_var;
	else
		name_len = ft_strlen(new_var);
	if (update_if_exists(env, new_var, name_len) == SUCCESS)
		return ;
	if (env->count >= env->capacity)
		env_expand(env);
	env->vars[env->count] = new_var;
	env->count++;
	env->vars[env->count] = NULL;
}

// env_get:
// 1. 遍历 vars，查找同名变量。
// 2. 找到后返回等号后的值。
// 3. 未找到返回 NULL。
// 获取指定名称的环境变量值
char	*env_get(t_env *env, const char *name)
{
	int		i;
	int		name_len;
	char	*equal_sign;

	if (!env || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (i < env->count)
	{
		if (ft_strncmp(env->vars[i], name, name_len) == 0
			&& env->vars[i][name_len] == '=')
		{
			equal_sign = ft_strchr(env->vars[i], '=');
			if (equal_sign)
				return (equal_sign + 1);
		}
		i++;
	}
	return (NULL);
}

// env_unset:
// 1. 遍历 vars，查找同名变量。
// 2. 找到后释放并将后续变量前移，count--。
// 3. 保证 vars 以 NULL 结尾。
// 删除指定名称的环境变量
void	env_unset(t_env *env, const char *name)
{
	int	i;
	int	j;
	int	name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (i < env->count)
	{
		if (ft_strncmp(env->vars[i], name, name_len) == 0
			&& env->vars[i][name_len] == '=')
		{
			free(env->vars[i]);
			j = i;
			while (j < env->count - 1)
			{
				env->vars[j] = env->vars[j + 1];
				j++;
			}
			env->count--;
			env->vars[env->count] = NULL;
			return ;
		}
		i++;
	}
}
