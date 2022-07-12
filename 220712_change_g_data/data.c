/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:31:33 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 16:37:55 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	free_data_lexer(t_data *data)
{
	int	i;

	i = 0;
	if (data->lexer.ptype)
		free(data->lexer.ptype);
	if (data->lexer.pptokens)
	{
		while (data->lexer.pptokens[i])
		{
			free(data->lexer.pptokens[i]);
			i++;
		}
		free(data->lexer.pptokens);
	}
	ft_bzero(&data->lexer, sizeof(t_lexer));
}

void	free_data_heredoc_delimiter(t_data *data)
{
	int	i;

	i = 0;
	if (data->heredoc_delimiter)
	{
		while (data->heredoc_delimiter[i])
		{
			free(data->heredoc_delimiter[i]);
			i++;
		}
		free(data->heredoc_delimiter);
		data->heredoc_delimiter = NULL;
	}
}

void	free_data_heredoc_fd(t_data *data)
{
	int	i;

	i = 0;
	if (!data->heredoc_fd)
		return ;
	while (i < data->heredoc_cnt)
	{
		close(data->heredoc_fd[i].fd[0]);
		close(data->heredoc_fd[i].fd[1]);
		i++;
	}
	free(data->heredoc_fd);
	data->heredoc_fd = NULL;
}

void	reset_data(t_data *data)
{
	data->tokens_cnt = 0;
	data->redirection_cnt = 0;
	data->pipe_cnt = 0;
	data->p_flag = 0;
	free_data_heredoc_fd(data);
	free_data_heredoc_delimiter(data);
	data->heredoc_cnt = 0;
	free_data_lexer(data);
	free_data_ast(data);
}
