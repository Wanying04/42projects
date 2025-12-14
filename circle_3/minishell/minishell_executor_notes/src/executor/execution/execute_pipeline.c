/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:41 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 19:07:56 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 检查管道命令链是否合法（不能有空命令）
// is_valid_pipeline:
// 1. 遍历命令链表，若有空命令（如连续两个 |），报错并返回 FAILURE。
// 2. 全部合法返回 SUCCESS。
static int	is_valid_pipeline(t_command *cmd)
{
	while (cmd)
	{
		if (!cmd->argv || !cmd->argv[0])
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\\n",
				STDERR_FILENO);
			return (FAILURE);
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

// execute_pipeline:
// 1. 先检查管道链合法性，若不合法直接返回语法错误码。
// 2. 合法则调用 execute_pipeline_core 执行。
// 执行管道命令的入口函数
int	execute_pipeline(t_command *cmd, t_env *env)
{
	if (is_valid_pipeline(cmd) != SUCCESS)
		return (SYNTAX_ERROR);
	return (execute_pipeline_core(cmd, env));
}
