/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:53:35 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:51:38 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * builtin_exit 主流程
 * 1. 若为主进程，输出 exit
 * 2. 检查参数，若有参数则判断是否合法数字
 *    - 非数字或溢出则报错并 exit(2)
 * 3. 若参数超过 1 个，报错并返回 FAILURE
 * 4. 规范化退出码到 0-255
 * 5. 清理历史和环境变量，退出进程
 */
int	builtin_exit(t_command *cmd, t_env *env)
{
       int     exit_status;

       // 1. 若为主进程（无前置命令），输出 exit
       if (!cmd->prev)
	       write(1, "exit\n", 5);

       exit_status = 0;

       // 2. 检查参数，若有则判断是否合法数字
       if (cmd->argv[1])
       {
	       if (!is_integer(cmd->argv[1]) || !ft_atol(cmd->argv[1], &exit_status))
	       {
		       write(2, "minishell: exit: numeric argument required\n", 43);
		       exit(2);
	       }
       }

       // 3. 若参数超过 1 个，报错并返回 FAILURE
       if (cmd->argv[1] && cmd->argv[2])
       {
	       write(2, "minishell: exit: too many arguments\n", 36);
	       return (FAILURE);
       }

       // 4. 规范化退出码到 0-255
       exit_status = exit_status % 256;
       if (exit_status < 0)
	       exit_status += 256;

       // 5. 清理历史和环境变量，退出进程
       rl_clear_history();
       env_destroy(env);
       exit(exit_status);
}
