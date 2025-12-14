/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:00:31 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:49:34 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * 功能：解析 cd 命令的目标路径
 * 1. 如果没有参数或参数为空，返回 HOME 目录
 * 2. 如果参数为 "-"，返回 OLDPWD 目录
 * 3. 否则尝试波浪号扩展
 * 4. 若有扩展则标记 should_free 以便后续释放
 */
static char	*resolve_cd_path(char *arg, t_env *env, int *should_free)
{
	char	*expanded;

	*should_free = 0;
	if (!arg || arg[0] == '\0')
		return (env_get(env, "HOME"));
	if (ft_strncmp(arg, "-", 2) == 0 && arg[1] == '\0')
		return (env->pwd->oldpwd);
	expanded = expand_tilde(arg, env);
	if (expanded && expanded != arg)
		*should_free = 1;
	if (expanded)
		return (expanded);
	return (arg);
}

/*
 * 功能：获取 cd 命令的最终路径，并处理相关错误
 * 1. 检查 "cd -" 时 OLDPWD 是否存在，不存在则报错
 * 2. 调用 resolve_cd_path 获取目标路径
 * 3. 若路径不存在，区分 HOME/OLDPWD 未设置的报错
 */
static char	*get_cd_path(char *arg, t_env *env, int *err, int *should_free)
{
	char	*path;

	if (arg && ft_strncmp(arg, "-", 2) == 0 && arg[1] == '\0'
		&& !env->pwd->oldpwd)
	{
		printf("cd: OLDPWD not set\n");
		*err = 1;
		return (NULL);
	}
	path = resolve_cd_path(arg, env, should_free);
	if (!path)
	{
		if (!arg || arg[0] == '\0')
			printf("cd: HOME not set\n");
		else
			printf("cd: OLDPWD not set\n");
		*err = 1;
		return (NULL);
	}
	*err = 0;
	return (path);
}

/*
 * 功能：执行 chdir 并更新环境变量
 * 1. 尝试切换目录，失败则报错并释放 old_cwd
 * 2. 若参数为 "-"，切换后打印新路径
 * 3. 获取当前工作目录，若失败则用逻辑路径
 * 4. 更新 PWD 和 OLDPWD 环境变量
 */
static int	do_cd_and_update_env(char *path, char *old_cwd,
	   t_command *cmd, t_env *env)
{
	char	*temp;

	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		free(old_cwd);
		return (FAILURE);
	}
	if (cmd->argv[1] && ft_strncmp(cmd->argv[1], "-", 2) == 0
		&& cmd->argv[1][1] == '\0')
		printf("%s\n", path);
	temp = getcwd(NULL, 0);
	if (!temp)
		temp = build_logical_path(env->pwd->pwd, cmd->argv[1]);
	update_pwd_oldpwd(env, old_cwd, temp);
	return (SUCCESS);
}

/*
 * builtin_cd 主流程
 * 1. 检查参数个数，若多于 1 个参数报错
 * 2. 获取当前工作目录，若失败则尝试用环境变量中的 pwd
 * 3. 获取目标路径，若失败则释放 old_cwd 并返回
 * 4. 切换目录并更新环境变量
 * 5. 若路径是动态分配的则释放
 */
int	builtin_cd(t_command *cmd, t_env *env)
{
       char    *path;
       char    *old_cwd;
       int             ret;
       int             should_free;

       // 1. 检查参数个数，cd 只允许一个参数
       if (cmd->argv[1] && cmd->argv[2])
	       return (write(2, "minishell: cd: too many arguments\n", 34), FAILURE);

       // 2. 获取当前工作目录，若失败则尝试用环境变量中的 pwd
       old_cwd = getcwd(NULL, 0);
       if (!old_cwd && env && env->pwd && env->pwd->pwd)
	       old_cwd = ft_strdup(env->pwd->pwd);
       if (!old_cwd)
	       return (perror("minishell: cd"), FAILURE);

       // 3. 获取目标路径，包含 HOME/OLDPWD 检查和错误处理
       path = get_cd_path(cmd->argv[1], env, &ret, &should_free);
       if (!path)
       {
	       free(old_cwd);
	       return (ret);
       }

       // 4. 切换目录并更新环境变量
       ret = do_cd_and_update_env(path, old_cwd, cmd, env);

       // 5. 若路径是动态分配的则释放
       if (should_free)
	       free(path);
       return (ret);
}
