/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:39:26 by yukim             #+#    #+#             */
/*   Updated: 2022/07/07 21:47:01 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	rl_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd);
// static int	is_heredoc_env(char *value);

void	exec_heredoc(int i, int *idx)
{
	char	*delimiter;

	if (ft_strncmp("<<", g_data.lexer.pptokens[i], -1))
	{
		delimiter = g_data.lexer.pptokens[i + 1];
		rl_heredoc(delimiter, &g_data.heredoc_fd[*idx]);
		(*idx)++;
	}
}

static void	rl_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd)
{
	char	*input_str;
	// char	*env_str;

	while (1)
	{
		input_str = readline("heredoc > ");
		if (ft_strncmp(input_str, delimiter, -1))
		{
			close(heredoc_fd->fd[1]);
			break ;
		}
		// is_env(input_str)
		// if (ft_strchr(input_str, '$'))
		write(heredoc_fd->fd[1], input_str, ft_strlen(input_str));
		write(heredoc_fd->fd[1], "\n", 1);
	}
	close(heredoc_fd->fd[1]);
}

// static int	is_heredoc_env(char *value)
// {
// 	int	i;
// 	int	quote;

// 	i = 0;
// 	while (value[i])
// 	{
// 		quote = is_quote(value[i]);
// 		if (value[i] && quote)
// 		{
// 			i++;
// 			while (value[i] && quote != is_quote(value[i]))
// 			{
// 				// if (quote == DOUBLE_QUOTE && value[i] == '$' && is_quote(value[i + 1])== DOUBLE_QUOTE)
// 				// 	return (FALSE);
// 				if (quote == DOUBLE_QUOTE && value[i] == '$')
// 				{
// 					if (is_quote(value[i + 1])== DOUBLE_QUOTE)
// 						return (FALSE);
// 					else
// 						return (TRUE);
// 				}
// 				i++;
// 			}
// 		}
// 		else if (quote == 0 && value[i] == '$' && value[i + 1] != '\0')
// 			return (TRUE);
// 		i++;
// 	}
// 	return (FALSE);
// }
