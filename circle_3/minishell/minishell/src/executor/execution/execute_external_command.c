/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:46:43 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 19:07:39 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 命令未找到时输出错误并退出
// command_not_found_error:
// 1. 打印命令未找到错误信息
// 2. 退出码 127
static void	command_not_found_error(char *cmd0)
{
	write(2, cmd0, ft_strlen(cmd0));
	write(2, ": command not found\n", 20);
	exit(127);
}

// resolve_command_path:
// 1. 查找命令路径，未找到直接退出 127
// 2. 路径不存在或不可执行、为目录等情况分别处理并退出
static char	*resolve_command_path(char *cmd0, t_env *env)
{
	char	*path;

	path = find_command_path(cmd0, env);
	if (!path)
		command_not_found_error(cmd0);
	if (access(path, F_OK) == -1)
	{
		perror(path);
		free(path);
		exit(127);
	}
	if (is_a_directory(path))
	{
		write(2, path, ft_strlen(path));
		write(2, ": Is a directory\n", 17);
		free(path);
		exit(126);
	}
	if (access(path, X_OK) == -1)
	{
		perror(path);
		free(path);
		exit(126);
	}
	return (path);
}

// child_process:
// 1. 重置信号为默认，保证子进程能被 Ctrl+C 正常中断
// 2. 处理重定向，失败直接退出
// 3. 查找命令路径并 execve 执行，失败输出错误
void	child_process(t_command *cmd, t_env *env)
{
	char	*path;

	reset_signals_to_default();
	if (handle_redirections(cmd, env, 0) != SUCCESS)
		exit(EXIT_FAILURE);
	path = resolve_command_path(cmd->argv[0], env);
	if (execve(path, cmd->argv, env_to_array(env)) == -1)
	{
		perror(path);
		free(path);
		exit(126);
	}
}

// wait_for_child:
// 1. 忽略主进程 SIGINT，等待子进程结束
// 2. 还原信号设置
// 3. 根据子进程退出类型返回不同退出码
static int	wait_for_child(pid_t pid)
{
	int					status;
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	else
		return (FAILURE);
}

// execute_external_command:
// 1. fork 子进程，子进程执行命令，父进程等待
// 2. fork 失败直接返回 FAILURE
// 3. 返回子进程退出码
int	execute_external_command(t_command *cmd, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (FAILURE);
	}
	else if (pid == 0)
	{
		child_process(cmd, env);
		exit (EXIT_FAILURE);
	}
	else
		return (wait_for_child(pid));
}
