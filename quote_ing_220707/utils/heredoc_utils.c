/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:39:26 by yukim             #+#    #+#             */
/*   Updated: 2022/07/11 18:48:48 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	rl_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd);
static int	is_heredoc_env(char *value);
static char	*replace_env_in_heredoc(char *origin);
static	int	get_len_with_envvalue_in_heredoc(char *origin);

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
	char	*env_str;

	while (1)
	{
		env_str = NULL;
		input_str = readline("heredoc > ");
		if (ft_strncmp(input_str, delimiter, -1))
		{
			close(heredoc_fd->fd[1]);
			break ;
		}
		if (is_heredoc_env(input_str))
		{
			env_str = replace_env_in_heredoc(input_str);
			free(input_str);
			input_str = env_str;
		}
		write(heredoc_fd->fd[1], input_str, ft_strlen(input_str));
		write(heredoc_fd->fd[1], "\n", 1);
	}
	close(heredoc_fd->fd[1]);
	close(heredoc_fd->fd[0]);
}

static int	is_heredoc_env(char *value)
{
	int	i;
	int	quote;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			quote = is_quote(value[i + 1]);
			if (quote == 0 || value[i + 1] != '\0')
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static char	*replace_env_in_heredoc(char *origin)
{
	int		i;
	int		j;
	char	*ret;
	int		all_len;
	char	*value;

	if (!origin)
		return (NULL);
	i = 0;
	j = 0;
	value = NULL;
	all_len = get_len_with_envvalue_in_heredoc(origin);
	ret = ft_calloc(all_len + 1, sizeof(char));
	if (!ret)
		ft_error("replace_env_in_heredoc : allocation failed\n");
	heredoc_replace_env_loop(origin, ret, value);
	return (ret);
}

static	int	get_len_with_envvalue_in_heredoc(char *origin)
{
	int	i;
	int	ret_len;
	int	quote;
	char	*value;

	if (!origin)
		return (0);
	i = 0;
	ret_len = 0;
	value = NULL;
	while (origin[i])
	{
		quote = is_quote(origin[i + 1]);
		if (origin[i] == '$' && origin[i + 1] == '?')
			heredoc_exit_status(value, &ret_len, &i);
		else if (origin[i] == '$' && origin[i + 1] != '\0' && quote == 0)
			get_len_with_envvalue_loop_in_heredoc(origin, value, &i, &ret_len);
		else
		{
			i++;
			ret_len++;
		}
	}
	return (ret_len);
}
