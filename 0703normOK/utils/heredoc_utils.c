/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:39:26 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:17:35 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	rl_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd);

void	exec_heredoc(int i, int *idx)
{
	char	*delimiter_without_quote;
	char	*delimiter;

	if (ft_strncmp("<<", g_data.lexer.pptokens[i], -1))
	{
		delimiter = g_data.lexer.pptokens[i + 1];
		if (delimiter[0] == '$' && delimiter[1] != '\0')
		{
			delimiter_without_quote = get_envv(delimiter + 1);
			if (!delimiter_without_quote)
				delimiter_without_quote = delimiter;
			rl_heredoc(delimiter_without_quote, &g_data.heredoc_fd[*idx]);
		}
		else
		{
			delimiter_without_quote = remove_quote(delimiter);
			rl_heredoc(delimiter_without_quote, &g_data.heredoc_fd[*idx]);
			if (delimiter != delimiter_without_quote)
				free(delimiter_without_quote);
		}
		(*idx)++;
	}
}

static void	rl_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd)
{
	char	*input_str;

	while (1)
	{
		input_str = readline("heredoc > ");
		if (ft_strncmp(input_str, delimiter, -1))
		{
			close(heredoc_fd->fd[1]);
			break ;
		}
		write(heredoc_fd->fd[1], input_str, ft_strlen(input_str));
		write(heredoc_fd->fd[1], "\n", 1);
	}
	close(heredoc_fd->fd[1]);
}
