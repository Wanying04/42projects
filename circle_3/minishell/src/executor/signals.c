/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:20:01 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:39:33 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================
// 信号处理相关函数
// =============================
// 重置信号处理为默认行为
// 将 SIGINT 和 SIGQUIT 信号恢复为默认处理方式，
// 用于执行外部命令时让子进程能被 Ctrl+C/Ctrl+\ 正常中断。
void	reset_signals_to_default(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// 忽略 SIGINT 信号（Ctrl+C）
// 忽略 SIGINT 信号（Ctrl+C），
// 用于 heredoc 等场景防止主进程被中断。
void	ignore_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

// 处理 SIGINT 信号（用于交互式终端）
// 主进程自定义 SIGINT 信号处理：
// 1. 设置全局标志，主循环可感知 Ctrl+C。
// 2. 清空当前输入行并刷新提示符。
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint_received = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// =============================
// 设置交互式 shell 的信号处理
// =============================
// 主循环专用信号设置：
// 1. SIGINT 绑定自定义 handler，保证 Ctrl+C 只刷新行不退出 shell。
// 2. SIGQUIT/SIGTSTP 忽略，防止 shell 被挂起或退出。
void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}
