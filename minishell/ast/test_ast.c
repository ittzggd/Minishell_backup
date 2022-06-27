/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:30:40 by yukim             #+#    #+#             */
/*   Updated: 2022/06/27 17:50:276 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	postorder_travel_ast(t_astnode *ast_node)
{
	int	*pid;
	int	pid_exit_status;
	int	i;
	int	pipe_line[2];
	int	prev_fd;
	int	tmp;

	pid = (int *)ft_calloc(data.pipe_cnt + 1, sizeof(int));
	if (!pid)
		exit(1);
	i = 0;
	prev_fd = -1;
	while (ast_node->nodetype == A_PIPE || ast_node->nodetype == A_COMMAND)
	{
		if (i < data.pipe_cnt)
		{
			if (pipe(pipe_line) < 0)
				exit(1);
		}
		pid[i] = fork();
		data.p_flag = TRUE;
		if (pid[i] < 0)
		{
			data.exit_status = 1; // 1하면 되는지 확인
			return ;  // exit
		}
		
		if (pid[i] == 0)
		{
			reset_signal();
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			close(pipe_line[0]);
			if (i < data.pipe_cnt) // 마지막 자식이 아니면
				dup2(pipe_line[1], STDOUT_FILENO);
			close(pipe_line[1]);
			if (ast_node->nodetype == A_PIPE)
				postorder_travel_command(ast_node->pleftchild);
			else
			{
				// pipe 다음 exit는 출력이 안되도록 수정 필요
				postorder_travel_command(ast_node);
			}
			exit(data.exit_status);
		}
		else // 부모 프로세스
		{
			// signal(SIGINT, SIG_IGN);
			// signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, handler_tmp);
			signal(SIGQUIT, handler_tmp);
			if (prev_fd != -1)
				close(prev_fd);
			if (i == data.pipe_cnt) // 마지막 커맨드 노드면
				close(pipe_line[0]);
			else
				prev_fd = pipe_line[0];
			close(pipe_line[1]);
			i++;
		}
		ast_node = ast_node->prightchild; // pipe_node
	}
	// 가장 마지막에 끝나는 자식까지 기다리기
	i = 0;
	while (i < data.pipe_cnt + 1)
	{
		waitpid(pid[i], &data.exit_status, 0);
		i++;
	} 

	// reset_signal();

	if (WIFEXITED(data.exit_status))
		data.exit_status = WEXITSTATUS(data.exit_status);
	else if (WIFSIGNALED(data.exit_status))
		data.exit_status = WTERMSIG(data.exit_status) + 128;
}

void	postorder_travel_command(t_astnode *cmdnode)
{
	if (cmdnode)
	{
		// reds
		postorder_travel_reds(cmdnode->pleftchild);
		
		// args
		if(cmdnode->prightchild->prightchild->pvalue_index)
			exec_cmd(cmdnode->prightchild);
	}
}

void	postorder_travel_reds(t_astnode *reds_node)
{
	// red
	if (reds_node->pleftchild)
	{
		goto_redirection(reds_node->pleftchild);
	}
	if(reds_node->prightchild)
	{
		postorder_travel_reds(reds_node->prightchild);
	}
	
}

void	goto_redirection(t_astnode *red_node)
{
	char	*red;
	char	*filename;

	if(!red_node->prightchild->pvalue_index)
		return ;
	red = data.lexer.pptokens[red_node->pleftchild->pvalue_index[0]];
	filename = data.lexer.pptokens[red_node->prightchild->pvalue_index[0]];
	if(ft_strncmp(red, "<", -1)) // 타입이 어떤 타입으로 확인해야할지 잘 모르겠음ㅜㅇ ㅜ
		in_red(filename);
	else if(ft_strncmp(red,">", -1))
		out_red(filename);
	else if(ft_strncmp(red,">>", -1))
		append_red(filename);
	else if(ft_strncmp(red,"<<", -1))
	 	heredoc(filename);
}
