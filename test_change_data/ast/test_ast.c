#include"../include/minishell.h"

void	postorder_travel_ast(t_astnode *ast_node)
{
	int	pid;
	int	i;

	pid = fork();
	if (pid < 0)
	{
		data.exit_status = 1; // 1하면 되는지 확인
		return ;
	}
	//sleep 10 | ls
	while (ast_node->nodetype == A_PIPE)
	{
		if (pid == 0)
			postorder_travel_command(ast_node->pleftchild);
		else // 부모 프로세스
		{
			// waitpid(-1, 0, WCONTINUED); 직렬, exit 하면 꼬임
			pid = fork();
			if (pid < 0)
			{
				data.exit_status = 1; // 1하면 되는지 확인
				return ;
			}
		}
		ast_node = ast_node->prightchild; // pipe
	}
	if (pid == 0 && ast_node->nodetype == A_COMMAND)
	{
		postorder_travel_command(ast_node);
	}
	// 가장 마지막에 끝나는 자식까지 기다리기
	i = -1;
	while (i < data.pipe_cnt)
	{
		wait(NULL);
		i++;
	}
	// if (ast_node)
	// {
	// 	if(ast_node->nodetype == A_COMMAND)
	// 	{
	// 		postorder_travel_command(ast_node, std_fd);
	// 		return;
	// 	}
	// 	else if (ast_node->nodetype == A_PIPE)
	// 	{
	// 		// 여기서 fork 필요하긴 함.
	// 		postorder_travel_command(ast_node->pleftchild, std_fd);
	// 		if (ast_node->prightchild->nodetype == A_COMMAND)
	// 		{
	// 			//여기서 fork 해야 자식에게 cmd node를 넘겨줌
	// 			postorder_travel_command(ast_node->prightchild, std_fd);
	// 			return ;
	// 		}
	// 		postorder_travel_ast(ast_node->prightchild, std_fd);
	// 	}
	// }
	// return ; 
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
	red = data.plexer->pptokens[red_node->pleftchild->pvalue_index[0]];
	filename = data.plexer->pptokens[red_node->prightchild->pvalue_index[0]];
	if(ft_strncmp(red, "<", -1)) // 타입이 어떤 타입으로 확인해야할지 잘 모르겠음ㅜㅇ ㅜ
		in_red(filename);
	else if(ft_strncmp(red,">", -1))
		out_red(filename);
	else if(ft_strncmp(red,">>", -1))
		append_red(filename);
	else if(ft_strncmp(red,"<<", -1))
		heredoc(filename);
}
