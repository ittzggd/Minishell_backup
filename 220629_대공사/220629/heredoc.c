/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:44:36 by yukim             #+#    #+#             */
/*   Updated: 2022/06/30 00:59:08 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	rl_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd);

void	preprocess_heredoc(void)
{
	char	*delimiter;
	int		i;
	int		idx;
	int		len;

	data.heredoc_flag = TRUE;
	data.exit_status = 0;
	data.heredoc_delimiter = ft_calloc(data.heredoc_cnt + 1, sizeof(char *));
	if (!data.heredoc_delimiter)
	{
		data.exit_status = 1;
		exit(data.exit_status);
	}
	data.heredoc_fd = ft_calloc(data.heredoc_cnt, sizeof(t_heredoc_fd *));
	if (!data.heredoc_fd)
	{
		data.exit_status = 1;
		exit(data.exit_status);
	}
	i = 0;
	idx = 0;
	while(idx < data.heredoc_cnt)
	{
		if (data.lexer.ptype[i] == T_REDIRECTION)
		{
			if(ft_strncmp("<<", data.lexer.pptokens[i], -1))
			{
				data.heredoc_delimiter[idx] = ft_strdup(data.lexer.pptokens[i + 1]);
				if(!data.heredoc_delimiter[idx])
				{
					data.exit_status = 1;
					exit(data.exit_status);
				}
				get_heredoc(data.heredoc_delimiter[idx], &data.heredoc_fd[idx]);
				idx++;
			}
		}
		i++;
	}
	data.heredoc_delimiter[idx] = NULL;
	data.heredoc_flag = FALSE;
}

void	get_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd)
{
	char	*delimiter_without_quote;
	
	if (pipe(heredoc_fd->fd) < 0)
	{
		data.exit_status = 1;
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
		// error
	}
	if (pid == 0)
	{
		signal(SIGINT, ft_sig_handler_in_heredoc);
		signal(SIGQUIT, ft_sig_handler_in_heredoc);
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
	else
	{
		close(heredoc_fd->fd[1]);
		waitpid(pid, &(data.exit_status), 0);
		printf("%d\n", data.heredoc_fd[1]);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (WIFEXITED(data.exit_status))
			data.exit_status = WEXITSTATUS(data.exit_status);
		// else if (WIFSIGNALED(data.exit_status))
		// 	data.exit_status = WTERMSIG(data.exit_status) + 128;
		data.p_flag = FALSE;
	}
}