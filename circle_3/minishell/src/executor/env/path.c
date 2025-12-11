/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:09:05 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:44:24 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================
// 命令路径查找主流程
// =============================
// 在指定目录查找可执行命令
// search_in_directory:
// 1. 拼接 dir/cmd 路径。
// 2. 检查可执行权限，若为目录则返回 NULL。
// 3. 找到可执行文件返回其路径副本。
static char	*search_in_directory(char *dir, char *cmd)
{
	char			full_path[1024];
	struct stat		path_stat;

	ft_strlcpy(full_path, dir, sizeof(full_path));
	ft_strlcat(full_path, "/", sizeof(full_path));
	ft_strlcat(full_path, cmd, sizeof(full_path));
	if (access(full_path, X_OK) == 0)
	{
		if (stat(full_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
			return (NULL);
		return (ft_strdup(full_path));
	}
	return (NULL);
}

// try_directory:
// 1. 临时截断 PATH 字符串，尝试在 current 目录查找命令。
// 2. 恢复 PATH 字符串原状。
static char	*try_directory(char *current, char *cmd, char *end)
{
	char	saved_char;
	char	*result;

	saved_char = *end;
	*end = '\0';
	result = search_in_directory(current, cmd);
	*end = saved_char;
	return (result);
}

// search_in_path:
// 1. 复制 PATH 环境变量，按 : 分割遍历每个目录。
// 2. 每个目录调用 try_directory 查找命令。
// 3. 找到即返回，未找到返回 NULL。
static char	*search_in_path(char *cmd, char *path_env)
{
	char	*path_copy;
	char	*current;
	char	*end;
	char	*result;

	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	current = path_copy;
	while (*current)
	{
		end = current;
		while (*end && *end != ':')
			end++;
		result = try_directory(current, cmd, end);
		if (result)
			return (free(path_copy), result);
		if (*end == ':')
			current = end + 1;
		else
			current = end;
	}
	return (free(path_copy), NULL);
}

// find_command_path:
// 1. 若 cmd 含 /，直接返回副本。
// 2. 否则查找 PATH 环境变量，遍历查找可执行文件。
// 3. 找到返回路径，未找到返回 NULL。
char	*find_command_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	*result;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = env_get(env, "PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);
	result = search_in_path(cmd, path_env);
	return (result);
}
