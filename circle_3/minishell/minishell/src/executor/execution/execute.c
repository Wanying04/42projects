/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:23:25 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:29:23 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 执行命令的主函数
int execute(t_command *cmd, t_env *env)
{
       // 如果命令或参数列表为空，直接返回成功
       if (!cmd || !cmd->argv)
	       return (SUCCESS);
       // 清理空参数
       cleanup_empty_args(cmd);
       // 如果没有命令但有重定向，只处理重定向
       if (!cmd->argv[0] && cmd->redirect_count > 0)
	       return (handle_redirections_only(cmd));
       // 如果没有命令且没有重定向，直接返回成功
       if (!cmd->argv[0])
	       return (SUCCESS);
       // 如果有下一个命令，执行管道
       if (cmd->next != NULL)
	       return (execute_pipeline(cmd, env));
       else
	       // 否则执行单个命令
	       return (execute_single_command(cmd, env));
}
