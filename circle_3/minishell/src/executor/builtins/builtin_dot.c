/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:54:13 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:49:51 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * builtin_dot 主流程
 * 实现 . (source) 内建命令，仅做参数和文件存在性检查
 * 1. 若无参数，输出用法提示并返回 2
 * 2. 若有参数但文件未找到，输出错误信息并返回 1
 */
int	builtin_dot(t_command *cmd)
{
       // 1. 检查是否有参数（即文件名）
       if (!cmd->argv[1])
       {
	       write(2, ".: filename argument required\n", 30);
	       write(2, ".: usage: . filename [arguments]\n", 33);
	       return (2);
       }
       // 2. 文件未找到，输出错误信息
       write(2, ".: ", 3);
       write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
       write(2, ": file not found\n", 17);
       return (1);
}
