/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:39:26 by yukim             #+#    #+#             */
/*   Updated: 2022/06/30 06:43:02 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	rl_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd);
static void	rl_heredoc_child(char *delimiter, t_heredoc_fd *heredoc_fd);

void	exec_heredoc(int i, int *idx)
{
	if (ft_strncmp("<<", data.lexer.pptokens[i], -1))
	{
		data.heredoc_delimiter[*idx] = ft_strdup(data.lexer.pptokens[i + 1]);
		get_heredoc(data.heredoc_delimiter[*idx], &data.heredoc_fd[*idx]);
		(*idx)++;
	}
}

void	get_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd)
{
	char	*delimiter_without_quote;

	if (pipe(heredoc_fd->fd) < 0)
	{
		ft_error_message("[Pipe ERROR] Heredoc failed\n", 1);
		return ;
	}
	if (delimiter[0] == '$' && delimiter[1] != '\0')
	{
		delimiter_without_quote = get_envv(delimiter + 1);
		if (!delimiter_without_quote)
			delimiter_without_quote = delimiter;
		rl_heredoc(delimiter_without_quote, data.heredoc_fd);
	}
	else
	{
		delimiter_without_quote = remove_quote(delimiter);
		rl_heredoc(delimiter_without_quote, data.heredoc_fd);
		if (delimiter != delimiter_without_quote)
			free(delimiter_without_quote);
	}
}

static void	rl_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd)
{
	char	*input_str;
	pid_t	pid;

	data.p_flag = TRUE;
	pid = fork();
	if (pid < 0)
	{
		ft_error_message("[Fork ERROR] Heredoc failed\n", 1);
		return ;
	}
	if (pid == 0)
	{
		signal(SIGINT, ft_sig_handler_in_heredoc);
		signal(SIGQUIT, ft_sig_handler_in_heredoc);
		rl_heredoc_child(delimiter, heredoc_fd);
	}
	else
	{
		close(heredoc_fd->fd[1]);
		waitpid(pid, &(data.exit_status), 0);
		if (WIFEXITED(data.exit_status))
			data.exit_status = WEXITSTATUS(data.exit_status);
		data.p_flag = FALSE;
	}
}

static void	rl_heredoc_child(char *delimiter, t_heredoc_fd *heredoc_fd)
{
	while (1)
	{
		input_str = readline("heredoc > ");
		if (ft_strncmp(input_str, delimiter, -1))
		{
			close(heredoc_fd->fd[1]);
			exit(data.exit_status);
		}
		write(heredoc_fd->fd[1], input_str, ft_strlen(input_str));
		write(heredoc_fd->fd[1], "\n", 1);
	}
}
