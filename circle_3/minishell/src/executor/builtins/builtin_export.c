/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:52:47 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:51:24 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 打印 export 的环境变量格式
static void	print_export_format(t_env *env)
{
	int		i;
	char	*equal_sign;
	char	*key;
	char	*value;

	i = 0;
	while (i < env->count)
	{
		equal_sign = ft_strchr(env->vars[i], '=');
		if (equal_sign)
		{
			key = ft_substr(env->vars[i], 0, equal_sign - env->vars[i]);
			value = equal_sign + 1;
			printf("declare -x %s=\"%s\"\n", key, value);
			free(key);
		}
		else
			printf("declare -x %s\n", env->vars[i]);
		i++;
	}
}
/*
 * 打印 export 的环境变量格式
 * 1. 遍历所有环境变量
 * 2. 若有等号，分割 key 和 value，按 declare -x key="value" 格式输出
 * 3. 否则只输出 key
 */
static void	print_export_format(t_env *env)
{
       int             i;
       char    *equal_sign;
       char    *key;
       char    *value;

       i = 0;
       while (i < env->count)
       {
               equal_sign = ft_strchr(env->vars[i], '=');
               if (equal_sign)
               {
                       key = ft_substr(env->vars[i], 0, equal_sign - env->vars[i]);
                       value = equal_sign + 1;
                       printf("declare -x %s=\"%s\"\n", key, value);
                       free(key);
               }
               else
                       printf("declare -x %s\n", env->vars[i]);
               i++;
       }
}

// 实现 export 内建命令
int	builtin_export(t_command *cmd, t_env *env)
{
	int	i;

	if (!cmd->argv[1])
	{
		print_export_format(env);
		return (SUCCESS);
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (!is_valid_var_name(cmd->argv[i]))
		{
			write(2, "minishell: export: `", 20);
			write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
			write(2, "' not a valid identifier\n", 26);
			return (FAILURE);
		}
		if (ft_strchr(cmd->argv[i], '='))
			env_set(env, cmd->argv[i]);
		i++;
	}
	return (SUCCESS);
}
/*
 * builtin_export 主流程
 * 1. 无参数时，按 export 格式打印所有环境变量
 * 2. 有参数时，依次校验变量名合法性
 *    - 非法则报错并返回
 *    - 合法且有 = 则设置环境变量
 */
int	builtin_export(t_command *cmd, t_env *env)
{
       int     i;

       // 1. 无参数，打印所有环境变量
       if (!cmd->argv[1])
       {
	       print_export_format(env);
	       return (SUCCESS);
       }
       i = 1;
       // 2. 依次处理每个参数
       while (cmd->argv[i])
       {
	       // 2.1 校验变量名是否合法
	       if (!is_valid_var_name(cmd->argv[i]))
	       {
		       write(2, "minishell: export: `", 20);
		       write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
		       write(2, "' not a valid identifier\n", 26);
		       return (FAILURE);
	       }
	       // 2.2 若有 = 则设置环境变量
	       if (ft_strchr(cmd->argv[i], '='))
		       env_set(env, cmd->argv[i]);
	       i++;
       }
       return (SUCCESS);
}
