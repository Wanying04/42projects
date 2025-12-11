/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:00:27 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:58:18 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 移除路径的最后一个部分
char	*remove_last_component(char *path)
{
/*
 * 移除路径的最后一个部分
 * 1. 若路径为根目录直接返回 "/"
 * 2. 找到最后一个斜杠，截断为上一级目录
 * 3. 若无斜杠返回 "."，若只有一个斜杠返回 "/"
 */
char	*remove_last_component(char *path)
{
	char	*last_slash;
	char	*result;

	if (!path || !*path)
		return (NULL);
	if (ft_strncmp(path, "/", 2) == 0)
		return (ft_strdup("/"));
	last_slash = ft_strrchr(path, '/');
	if (!last_slash)
		return (ft_strdup("."));
	if (last_slash == path)
		return (ft_strdup("/"));
	result = malloc(last_slash - path + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, path, last_slash - path + 1);
	return (result);
}

// 构建逻辑路径（如 cd ..）
char	*build_logical_path(char *current_pwd, char *target)
{
/*
 * 构建逻辑路径（如 cd ..）
 * 1. 若 target 为 ".." 或空，返回当前路径的上一级
 * 2. 其他情况暂不处理，返回 NULL
 */
char	*build_logical_path(char *current_pwd, char *target)
{
	if (!current_pwd || !target)
		return (NULL);
	if (ft_strncmp(target, "..", 3) == 0 || !target[0])
		return (remove_last_component(current_pwd));
	return (NULL);
}

// 设置环境变量
void	set_env_var(t_env *env, const char *name, const char *value)
{
/*
 * 设置环境变量
 * 1. 拼接 name 和 value 形成 "name=value"
 * 2. 调用 env_set 设置到环境变量中
 */
void	set_env_var(t_env *env, const char *name, const char *value)
{
	char	*eq;
	char	*env_str;

	eq = ft_strjoin(name, "=");
	if (!value || !eq)
		return ;
	env_str = ft_strjoin(eq, value);
	free(eq);
	if (env_str)
	{
		env_set(env, env_str);
		free(env_str);
	}
}

void	update_pwd_oldpwd(t_env *env, char *old_cwd, char *new_cwd)
{
/*
 * 更新 PWD 和 OLDPWD 环境变量
 * 1. 释放原有 oldpwd/pwd，赋新值
 * 2. 同步设置到环境变量中
 */
void	update_pwd_oldpwd(t_env *env, char *old_cwd, char *new_cwd)
{
	if (env->pwd->oldpwd)
		free(env->pwd->oldpwd);
	env->pwd->oldpwd = old_cwd;
	if (env->pwd->pwd)
		free(env->pwd->pwd);
	env->pwd->pwd = new_cwd;
	set_env_var(env, "OLDPWD", old_cwd);
	set_env_var(env, "PWD", new_cwd);
}
