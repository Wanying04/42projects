/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:52:25 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:52:25 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * 判断变量名是否合法
 * 1. 必须以字母或下划线开头
 * 2. 后续只能包含字母、数字或下划线，遇到等号停止
 */
int	is_valid_var_name(char *str)
{
       int     i;

       if (!str || !str[0])
	       return (0);
       if (!ft_isalpha(str[0]) && str[0] != '_')
	       return (0);
       i = 1;
       while (str[i] && str[i] != '=')
       {
	       if (!ft_isalnum(str[i]) && str[i] != '_')
		       return (0);
	       i++;
       }
       return (1);
}

/*
 * builtin_unset 主流程
 * 1. 若无参数直接返回
 * 2. 依次检查每个参数是否合法变量名，合法则 unset
 */
int	builtin_unset(t_command *cmd, t_env *env)
{
       int     i;

       // 1. 若无参数直接返回
       if (!cmd->argv[1])
	       return (SUCCESS);
       i = 1;
       // 2. 依次检查每个参数是否合法变量名，合法则 unset
       while (cmd->argv[i])
       {
	       if (is_valid_var_name(cmd->argv[i]))
		       env_unset(env, cmd->argv[i]);
	       i++;
       }
       return (SUCCESS);
}
