/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postorder_travel_ast.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:51:54 by yukim             #+#    #+#             */
/*   Updated: 2022/06/30 15:51:54 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static void	while_pipe_or_command(t_astnode *ast_node, pid_t *pid);
static void	c_in_while(int i, int *prev_fd, int *pipe_line, t_astnode *astnode);
static void	parent_in_while_pipe_or_cmd(int *prev_fd, int *pipe_line);

void	postorder_travel_ast(t_astnode *ast_node)
{
	pid_t	*pid;
	int		i;

	data.p_flag = TRUE;
	calloc_nullcheck(&pid, data.pipe_cnt + 1, sizeof(int));
	while_pipe_or_command(ast_node, pid);
	i = 0;
	while (i < data.pipe_cnt + 1)
	{
		waitpid(pid[i], &data.exit_status, 0);
		i++;
	} 
	if (WIFEXITED(data.exit_status))
		data.exit_status = WEXITSTATUS(data.exit_status);
	else if (WIFSIGNALED(data.exit_status))
		data.exit_status = WTERMSIG(data.exit_status) + 128;
}

static void	while_pipe_or_command(t_astnode *ast_node, pid_t *pid)
{
	int		i;
	int		pipe_line[2];
	int		prev_fd;

	i = 0;
	prev_fd = -1;
	while (ast_node->nodetype == A_PIPE || ast_node->nodetype == A_COMMAND)
	{
		if (i < data.pipe_cnt)
		{
			if (pipe(pipe_line) < 0)
				ft_error("[Pipe ERROR] ast failed\n");
		}
		pid[i] = fork();
		if (pid[i] < 0)
			ft_error("[Fork ERROR] ast failed\n");
		if (pid[i] == 0)
			c_in_while(i, &prev_fd, pipe_line, ast_node);
		parent_in_while_pipe_or_cmd(&prev_fd, pipe_line);
		i++;
		ast_node = ast_node->prightchild;
	}
}

static void	c_in_while(int i, int *prev_fd, int *pipe_line, t_astnode *astnode)
{
	reset_signal();
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	close(pipe_line[0]);
	if (i < data.pipe_cnt)
		dup2(pipe_line[1], STDOUT_FILENO);
	close(pipe_line[1]);
	if (astnode->nodetype == A_PIPE)
		postorder_travel_command(astnode->pleftchild);
	else
		postorder_travel_command(astnode);
	exit(data.exit_status);
}

static void	parent_in_while_pipe_or_cmd(int *prev_fd, int *pipe_line)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i == data.pipe_cnt)
		close(pipe_line[0]);
	else
		*prev_fd = pipe_line[0];
	close(pipe_line[1]);
}