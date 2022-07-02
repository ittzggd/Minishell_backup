/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:44:36 by yukim             #+#    #+#             */
/*   Updated: 2022/07/02 18:45:01 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	create_delimiter_list(void);
static void	heredoc_do_child(void);
static void	heredoc_do_parent(int pid);

void	preprocess_heredoc(void)
{
	char	*delimiter;
	int		len;
	pid_t	pid;

	data.heredoc_flag = TRUE;
	data.exit_status = 0;
	data.heredoc_delimiter = ft_calloc(data.heredoc_cnt + 1, sizeof(char *));
	if (!data.heredoc_delimiter)
		ft_error("[preprocess_heredoc] heredoc_delimiter: allocation failed");
	data.heredoc_fd = ft_calloc(data.heredoc_cnt, sizeof(t_heredoc_fd *));
	if (!data.heredoc_fd)
		ft_error("[preprocess_heredoc] heredoc_fd : allocation failed\n");
	create_delimiter_list();
	pid = fork();
	if(pid == 0)
		heredoc_do_chile();
	else
		heredoc_do_parent(pid);
	data.heredoc_flag = FALSE;
}

static void	create_delimiter_list(void)
{
	int		hd_idx;
	int		t_idx;
	char	**tokens;

	hd_idx = 0;
	t_idx = 0;
	tokens = data.lexer.pptokens;
	while (hd_idx < data.heredoc_cnt)
	{
		if (ft_strncmp("<<", tokens[t_idx], -1))
		{
			if (pipe(data.heredoc_fd[hd_idx].fd) < 0)
				ft_error("[Pipe ERROR] Heredoc failed\n");
			data.heredoc_delimiter[hd_idx] = ft_strdup(tokens[t_idx + 1]);
			hd_idx++;
		}
		t_idx++;
	}
}

static void	heredoc_do_child(void)
{
	int	i;
	int	idx;
	
	i = 0;
	idx = 0;
	data.p_flag = TRUE;
	signal(SIGINT, ft_sig_handler_in_heredoc);
	signal(SIGQUIT, ft_sig_handler_in_heredoc);
	while (idx < data.heredoc_cnt)
	{
		if (data.lexer.ptype[i] == T_REDIRECTION)
			exec_heredoc(i, &idx);
		i++;
	}
	data.heredoc_delimiter[idx] = NULL;
	data.heredoc_flag = FALSE;
	exit(data.exit_status);
}

static void	heredoc_do_parent(int pid)
{
	int	i;
	
	i = 0;
	waitpid(pid, &(data.exit_status), 0);
	if (WIFEXITED(data.exit_status))
		data.exit_status = WEXITSTATUS(data.exit_status);
	data.p_flag = FALSE;
	i = 0;
	while (i < data.heredoc_cnt)
	{
		close(data.heredoc_fd[i].fd[1]);
		i++;
	}
}
 