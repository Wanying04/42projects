/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:44:41 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 12:42:23 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================
// heredoc 处理主流程
// =============================
// 父进程处理 heredoc，等待子进程并设置输入重定向
// process_heredoc_parent:
// 1. 父进程等待子进程完成 heredoc 输入。
// 2. 若子进程被 Ctrl+C 中断，设置退出码 130 并返回失败。
// 3. 若 should_dup 为真，将 heredoc 管道读端 dup2 到标准输入。
static int	process_heredoc_parent(int read_fd, pid_t pid, t_env *env,
	int should_dup)
{
	int	status;

	ignore_sigint();
	waitpid(pid, &status, 0);
	setup_signals();
	rl_on_new_line();
	rl_replace_line("", 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		close(read_fd);
		env->exit_status = 130;
		return (FAILURE);
	}
	if (should_dup)
	{
		if (dup2(read_fd, STDIN_FILENO) == -1)
		{
			perror("minishell");
			close(read_fd);
			return (FAILURE);
		}
	}
	close(read_fd);
	return (SUCCESS);
}

// read_heredoc_input:
// 1. 子进程循环读取用户输入，遇到分隔符或 Ctrl+D 结束。
// 2. 支持变量展开，写入管道。
static int	read_heredoc_input(int write_fd, char *delimiter,
	t_env *env, int dont_expand)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "minishell: warning: heredoc delimited by EOF\n", 45);
			return (SUCCESS);
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\0')
		{
			free(line);
			return (SUCCESS);
		}
		expanded = expand_heredoc(line, env, dont_expand);
		write(write_fd, expanded, ft_strlen(expanded));
		write(write_fd, "\n", 1);
		free(line);
		free(expanded);
	}
}

// process_heredoc_child:
// 1. 子进程设置 SIGINT 默认，允许 Ctrl+C 终止。
// 2. 调用 read_heredoc_input 读取内容并写入管道。
static void	process_heredoc_child(int write_fd, char *delimiter,
	t_env *env, int dont_expand)
{
	signal(SIGINT, SIG_DFL);
	rl_catch_signals = 1;
	dup2(STDERR_FILENO, STDOUT_FILENO);
	read_heredoc_input(write_fd, delimiter, env, dont_expand);
	close(write_fd);
	exit(SUCCESS);
}

// process_heredoc:
// 1. 创建管道，fork 子进程。
// 2. 子进程负责读取 heredoc，父进程等待并处理结果。
// 3. 失败时关闭管道并返回 FAILURE。
int	process_heredoc(char *delimiter, t_env *env,
	int dont_expand, int should_dup)
{
	int					pipefd[2];
	pid_t				pid;

	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		return (FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		close(pipefd[0]);
		close(pipefd[1]);
		return (FAILURE);
	}
	if (pid == 0)
		process_heredoc_child(pipefd[1], delimiter, env, dont_expand);
	else
	{
		close(pipefd[1]);
		return (process_heredoc_parent(pipefd[0], pid, env, should_dup));
	}
	return (SUCCESS);
}
