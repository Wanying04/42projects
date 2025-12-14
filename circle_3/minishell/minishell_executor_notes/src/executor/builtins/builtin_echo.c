/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:55:51 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:50:41 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * 判断参数是否为 -n 选项
 * 1. 必须以 "-n" 开头，且后续只能有 n 字符
 * 2. 用于 echo 是否输出换行
 */
static int	is_n_option(char *str)
{
       int     i;

       if (!str || str[0] != '-' || str[1] != 'n')
	       return (0);
       i = 1;
       while (str[i])
       {
	       if (str[i] != 'n')
		       return (0);
	       i++;
       }
       return (1);
}

/*
 * 打印 echo 命令的参数
 * 1. 跳过特殊标记参数（\x01, \x02），仅输出空格
 * 2. 其余参数正常输出，参数间加空格
 * 3. 根据 newline 决定是否输出换行
 */
static void	echo_print_args(t_command *cmd, int i, int newline)
{
       while (cmd->argv[i])
       {
	       // 1. 跳过特殊标记参数，仅输出空格
	       if (ft_strlen(cmd->argv[i]) == 2
		       && (cmd->argv[i][0] == '\x01' || cmd->argv[i][0] == '\x02'))
	       {
		       if (cmd->argv[i + 1])
			       write(1, " ", 1);
	       }
	       else
	       {
		       // 2. 正常输出参数
		       write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		       if (cmd->argv[i + 1])
			       write(1, " ", 1);
	       }
	       i++;
       }
       // 3. 根据 newline 决定是否输出换行
       if (newline)
	       write(1, "\n", 1);
}

/*
 * builtin_echo 主流程
 * 1. 跳过所有 -n 选项，决定是否输出换行
 * 2. 输出剩余参数，参数间加空格
 * 3. 若未指定 -n，末尾输出换行
 */
int	builtin_echo(t_command *cmd)
{
       int     i;
       int     newline;

       i = 1;
       newline = 1;
       // 1. 跳过所有 -n 选项，若有则不换行
       while (cmd->argv[i] && is_n_option(cmd->argv[i]))
       {
	       newline = 0;
	       i++;
       }
       // 2. 输出参数，3. 根据 newline 决定是否换行
       echo_print_args(cmd, i, newline);
       return (SUCCESS);
}
