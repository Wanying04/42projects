/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:44:47 by wtang             #+#    #+#             */
/*   Updated: 2025/12/11 19:07:24 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 处理单个重定向（包括文件和 heredoc），并判断是否为歧义重定向
// process_single_redirection:
// 1. 检查 file 是否为歧义重定向（如 $VAR 未展开为有效路径）。
// 2. heredoc 类型调用 process_heredoc，其余类型调用 handle_file_redirection。
static int	process_single_redirection(t_redirect *redir, t_env *env,
	int dont_expand, int should_dup)
{
	if (redir->file && redir->file[0] == '$' && !is_integer(&redir->file[0]))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (FAILURE);
	}
	if (redir->type == REDIR_HEREDOC)
		return (process_heredoc(redir->file, env, dont_expand, should_dup));
	return (handle_file_redirection(redir, should_dup));
}

// handle_redirections:
// 1. 先遍历所有重定向，记录最后一个输入/heredoc 的下标。
// 2. 再遍历所有重定向，只有最后一个输入/heredoc 才真正 dup2，前面的只打开关闭。
// 3. 只要有一步失败，立即返回 FAILURE。
// 4. 全部成功返回 SUCCESS。
// 依次处理命令的所有重定向，保证输入重定向只保留最后一个
int	handle_redirections(t_command *cmd, t_env *env, int i)
{
	int	last_input_redir;
	int	should_dup;

	last_input_redir = -1;
	while (i < cmd->redirect_count)
	{
		if (cmd->redirects[i].type == REDIR_IN
			|| cmd->redirects[i].type == REDIR_HEREDOC)
			last_input_redir = i;
		i++;
	}
	i = 0;
	while (i < cmd->redirect_count)
	{
		should_dup = 1;
		if ((cmd->redirects[i].type == REDIR_IN || cmd->redirects[i].type
				== REDIR_HEREDOC) && i != last_input_redir)
			should_dup = 0;
		if (process_single_redirection(&cmd->redirects[i], env,
				cmd->dont_expand, should_dup) != SUCCESS)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
