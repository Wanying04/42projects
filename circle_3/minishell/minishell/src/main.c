/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:26:02 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 19:05:32 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 全局变量：用于接收 SIGINT 信号（如 Ctrl+C），让主循环能感知用户中断。
volatile sig_atomic_t	g_sigint_received = 0;

/*
 * 用户输入处理流程：
 * 1. 检查输入是否为空或全空白，若是则直接返回。
 * 2. 有效输入加入历史记录，便于命令回溯。
 * 3. 解析输入为命令链表。
 * 4. 若解析成功则执行命令链表，并释放内存。
 */
static void	process_input(char *input, t_env *env)
{
	t_command	*cmd_list;

	if (!*input || is_empty_input(input))
		return ;
	add_history(input);
	cmd_list = parse_input(input, env);
	if (cmd_list)
	{
		env->exit_status = execute(cmd_list, env);
		free_command(cmd_list);
	}
}

/*
 * minishell 主程序入口：
 * 1. 忽略 argc/argv，仅用 envp 初始化环境变量。
 * 2. 设置信号处理，保证 Ctrl+C 等能正确响应。
 * 3. 主循环不断读取用户输入：
 *    - 每次循环重置信号标志。
 *    - 读取一行输入，若收到 Ctrl+C 设置退出码 130。
 *    - 若输入为 NULL（Ctrl+D），清理环境并退出。
 *    - 非空输入则进入命令解析与执行流程。
 *    - 每次循环释放输入内存。
 */
int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*input;

	(void)argc;
	(void)argv;
	setup_signals();
	env = env_create(envp);
	if (!env)
		return (1);
	while (1)
	{
		g_sigint_received = 0;
		input = readline("minishell$ ");
		if (g_sigint_received)
			env->exit_status = 130;
		if (!input)
		{
			cleanup_and_exit(env);
			break ;
		}
		if (*input != '\0')
			process_input(input, env);
		free(input);
	}
	return (0);
}
