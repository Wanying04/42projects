/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:54:01 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:50:53 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * builtin_env 主流程
 * 1. 检查参数，env 不接受多余参数，有则报错
 * 2. 遍历并打印所有环境变量
 */
int	builtin_env(t_command *cmd, t_env *env)
{
       int     i;

       (void)cmd;
       i = 0;
       // 1. 检查参数，env 只允许无参数
       if (cmd->argv[1])
       {
	       write(2, "minishell: env: argument env only\n", 34);
	       return (SYNTAX_ERROR);
       }
       // 2. 遍历并打印所有环境变量
       while (i < env->count)
       {
	       printf("%s\n", env->vars[i]);
	       i++;
       }
       return (SUCCESS);
}
