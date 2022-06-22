// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   save_test_ast.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/22 17:30:46 by yukim             #+#    #+#             */
// /*   Updated: 2022/06/22 17:30:45 by hejang           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include"../include/minishell.h"

// void	postorder_travel_ast(t_astnode *ast_node, int *std_fd)
// {
// 	int	*pid;
// 	int	pid_exit_status;
// 	int	i;
// 	int	pipe_line[2];
// 	int	prev_fd;

// 	pid = (int *)ft_calloc(data.pipe_cnt + 1, sizeof(int));
// 	if (!pid)
// 		exit(1);
// 	i = 0;
// 	prev_fd = 0;
// 	if (pipe(pipe_line) < 0)
// 		exit(1);
// 	pid[i] = fork();
// 	if (pid[i] < 0)
// 	{
// 		data.exit_status = 1; // 1하면 되는지 확인
// 		return ;  // exit
// 	}
// 	while (ast_node->nodetype == A_PIPE)
// 	{
// 		if (pid[i] == 0)
// 		{
// 			if (prev_fd)
// 			{
// 				dup2(prev_fd, STDIN_FILENO);
// 				close(prev_fd);
// 			}
// 			close(pipe_line[0]);
// 			dup2(pipe_line[1], STDOUT_FILENO);
// 			close(pipe_line[1]);

// 			postorder_travel_command(ast_node->pleftchild);
// 			exit(data.exit_status);
// 		}
// 		else // 부모 프로세스
// 		{
// 			i++;
// 			if (pipe(pipe_line) < 0)
// 				exit(1);
// 			pid[i] = fork();
// 			if (pid[i] < 0)
// 			{
// 				data.exit_status = 1; // 1하면 되는지 확인
// 				return ;  // exit
// 			}
// 			if (prev_fd)
// 				close(prev_fd);
// 			prev_fd = pipe_line[0];
// 			close(pipe_line[1]);
// 		}
// 		ast_node = ast_node->prightchild; // pipe_node
// 	}
// 	if (pid[i] == 0 && ast_node->nodetype == A_COMMAND)
// 	{
// 		postorder_travel_command(ast_node);
// 		pid_exit_status = data.exit_status;
// 		exit(data.exit_status);
// 	}
// 	// 가장 마지막에 끝나는 자식까지 기다리기
// 	data.exit_status = pid_exit_status;
// 	i = 0;
// 	while (i < data.pipe_cnt + 1)
// 	{
// 		waitpid(pid[i], &data.exit_status, 0);
// 		i++;
// 	}

// 	// if (ast_node)
// 	// {
// 	// 	if(ast_node->nodetype == A_COMMAND)
// 	// 	{
// 	// 		postorder_travel_command(ast_node, std_fd);
// 	// 		return;
// 	// 	}
// 	// 	else if (ast_node->nodetype == A_PIPE)
// 	// 	{
// 	// 		// 여기서 fork 필요하긴 함.
// 	// 		postorder_travel_command(ast_node->pleftchild, std_fd);
// 	// 		if (ast_node->prightchild->nodetype == A_COMMAND)
// 	// 		{
// 	// 			//여기서 fork 해야 자식에게 cmd node를 넘겨줌
// 	// 			postorder_travel_command(ast_node->prightchild, std_fd);
// 	// 			return ;
// 	// 		}
// 	// 		postorder_travel_ast(ast_node->prightchild, std_fd);
// 	// 	}
// 	// }
// 	// return ; 
// }

// void	postorder_travel_command(t_astnode *cmdnode)
// {
// 	if (cmdnode)
// 	{
// 		// reds
// 		postorder_travel_reds(cmdnode->pleftchild);
		
// 		// args
// 		if(cmdnode->prightchild->prightchild->pvalue_index)
// 			exec_cmd(cmdnode->prightchild);
// 	}
// }

// void	postorder_travel_reds(t_astnode *reds_node)
// {
// 	// red
// 	if (reds_node->pleftchild)
// 	{
// 		goto_redirection(reds_node->pleftchild);
// 	}
// 	if(reds_node->prightchild)
// 	{
// 		postorder_travel_reds(reds_node->prightchild);
// 	}
	
// }

// void	goto_redirection(t_astnode *red_node)
// {
// 	char	*red;
// 	char	*filename;

// 	if(!red_node->prightchild->pvalue_index)
// 		return ;
// 	red = data.plexer->pptokens[red_node->pleftchild->pvalue_index[0]];
// 	filename = data.plexer->pptokens[red_node->prightchild->pvalue_index[0]];
// 	if(ft_strncmp(red, "<", -1)) // 타입이 어떤 타입으로 확인해야할지 잘 모르겠음ㅜㅇ ㅜ
// 		in_red(filename);
// 	else if(ft_strncmp(red,">", -1))
// 		out_red(filename);
// 	else if(ft_strncmp(red,">>", -1))
// 		append_red(filename);
// 	else if(ft_strncmp(red,"<<", -1))
// 		heredoc(filename);
// }
