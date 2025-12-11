/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:52:36 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:52:09 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * builtin_pwd 主流程
 * 1. 优先使用环境变量中的 pwd 字段作为当前目录
 * 2. 若无 pwd 字段，则调用 getcwd 获取当前目录
 *    - 获取失败则报错
 *    - 成功则输出当前目录
 */
int	builtin_pwd(t_command *cmd, t_env *env)
{
       char    *pwd;
       char    cwd[4096];

       (void)cmd;
       // 1. 优先使用环境变量中的 pwd 字段
       if (env && env->pwd && env->pwd->pwd)
       {
	       pwd = env->pwd->pwd;
	       write(1, pwd, ft_strlen(pwd));
	       write(1, "\n", 1);
	       return (SUCCESS);
       }
       else
       {
	       // 2. 若无 pwd 字段，则调用 getcwd
	       if (getcwd(cwd, sizeof(cwd)) == NULL)
	       {
		       perror("minishell: pwd");
		       return (FAILURE);
	       }
	       write(1, cwd, ft_strlen(cwd));
	       write(1, "\n", 1);
	       return (SUCCESS);
       }
}
