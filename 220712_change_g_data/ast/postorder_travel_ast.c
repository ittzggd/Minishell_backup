/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postorder_travel_ast.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:51:54 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 17:27:46 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static void	while_pipe_or_command(t_data *data, t_astnode *ast_node, pid_t *pid);
static void	c_in_while(t_data *data, int i, int *prev_fd, int *pipe_line, t_astnode *astnode);
static void	parent_in_while_pipe_or_cmd(t_data *data, int i, int *prev_fd, int *pipe_line);

void	postorder_travel_ast(t_data *data, t_astnode *ast_node)
{
	pid_t	*pid;
	int		i;

	data->p_flag = TRUE;
	pid = ft_calloc(data->pipe_cnt + 1, sizeof(int));
	if (!pid)
		ft_error("postorder_travel_ast : allocation failed\n");
	while_pipe_or_command(data, ast_node, pid);
	i = 0;
	while (i < data->pipe_cnt + 1)
	{
		waitpid(pid[i], &g_exit_status, 0);
		i++;
	}
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = WTERMSIG(g_exit_status) + 128;
	free(pid);
}

static void	while_pipe_or_command(t_data *data, t_astnode *ast_node, pid_t *pid)
{
	int		i;
	int		pipe_line[2];
	int		prev_fd;

	i = 0;
	prev_fd = NOT_USED;
	while (ast_node->nodetype == A_PIPE || ast_node->nodetype == A_COMMAND)
	{
		if (i < data->pipe_cnt)
		{
			if (pipe(pipe_line) < 0)
				ft_error("[Pipe ERROR] ast failed\n");
		}
		pid[i] = fork();
		if (pid[i] < 0)
			ft_error("[Fork ERROR] ast failed\n");
		if (pid[i] == 0)
			c_in_while(data, i, &prev_fd, pipe_line, ast_node);
		parent_in_while_pipe_or_cmd(data, i, &prev_fd, pipe_line);
		i++;
		ast_node = ast_node->prightchild;
	}
}

static void	c_in_while(t_data *data, int i, int *prev_fd, int *pipe_line, t_astnode *astnode)
{
	reset_signal();
	if (*prev_fd != NOT_USED)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	close(pipe_line[0]);
	if (i < data->pipe_cnt)
		dup2(pipe_line[1], STDOUT_FILENO);
	close(pipe_line[1]);
	if (astnode->nodetype == A_PIPE)
		postorder_travel_command(data, astnode->pleftchild);
	else
		postorder_travel_command(data, astnode);
	exit(g_exit_status);
}

static void	parent_in_while_pipe_or_cmd(t_data *data, int i, int *prev_fd, int *pipe_line)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (*prev_fd != NOT_USED)
		close(*prev_fd);
	if (i == data->pipe_cnt)
		close(pipe_line[0]);
	else
		*prev_fd = pipe_line[0];
	close(pipe_line[1]);
}
