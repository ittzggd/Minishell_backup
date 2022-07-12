/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:44:36 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 17:10:38 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	create_delimiter_list(t_data *data);
static void	heredoc_do_child(t_data *data);
static void	heredoc_do_parent(t_data *data, int pid);

void	preprocess_heredoc(t_data *data)
{
	int		count;
	pid_t	pid;

	data->heredoc_flag = TRUE;
	g_exit_status = 0;
	count = data->heredoc_cnt;
	data->heredoc_delimiter = ft_calloc(count + 1, sizeof(char *));
	if (!data->heredoc_delimiter)
		ft_error("[preprocess_heredoc] heredoc_delimiter: allocation failed\n");
	data->heredoc_fd = ft_calloc(count, sizeof(t_heredoc_fd *));
	if (!data->heredoc_fd)
		ft_error("[preprocess_heredoc] heredoc_fd : allocation failed\n");
	create_delimiter_list(data);
	pid = fork();
	if (pid == 0)
		heredoc_do_child(data);
	else
		heredoc_do_parent(data, pid);
	data->heredoc_flag = FALSE;
}

static void	create_delimiter_list(t_data *data)
{
	int		hd_idx;
	int		t_idx;
	char	**tokens;

	hd_idx = 0;
	t_idx = 0;
	tokens = data->lexer.pptokens;
	while (hd_idx < data->heredoc_cnt)
	{
		if (data->lexer.ptype[t_idx] == T_REDIRECTION)
		{
			if (ft_strncmp("<<", tokens[t_idx], -1))
			{
				if (pipe(data->heredoc_fd[hd_idx].fd) < 0)
					ft_error("[Pipe ERROR] Heredoc failed\n");
				data->heredoc_delimiter[hd_idx] = ft_strdup(tokens[t_idx + 1]);
				hd_idx++;
			}
		}
		t_idx++;
	}
}

static void	heredoc_do_child(t_data *data)
{
	int	i;
	int	idx;

	i = 0;
	idx = 0;
	data->p_flag = TRUE;
	signal(SIGINT, ft_sig_handler_in_heredoc_sigint);
	signal(SIGQUIT, ft_sig_handler_in_heredoc_sigquit);
	while (idx < data->heredoc_cnt)
	{
		if (data->lexer.ptype[i] == T_REDIRECTION)
			exec_heredoc(data, i, &idx);
		i++;
	}
	data->heredoc_delimiter[idx] = NULL;
	data->heredoc_flag = FALSE;
	exit(g_exit_status);
}

static void	heredoc_do_parent(t_data *data, int pid)
{
	int	i;

	i = 0;
	waitpid(pid, &(g_exit_status), 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	data->p_flag = FALSE;
	i = 0;
	while (i < data->heredoc_cnt)
	{
		close(data->heredoc_fd[i].fd[1]);
		i++;
	}
}
