#include"../include/minishell.h"

void	postorder_travel_ast(t_astnode *ast_node)
{
	if (ast_node)
	{
		if(ast_node->nodetype == A_COMMAND)
		{
			postorder_travel_command(ast_node);
			return;
		}
		else if (ast_node->nodetype == A_PIPE)
		{
			// 여기서 fork 필요하긴 함.
			postorder_travel_command(ast_node->pleftchild);
			if (ast_node->prightchild->nodetype == A_COMMAND)
			{
				//여기서 fork 해야 자식에게 cmd node를 넘겨줌
				postorder_travel_command(ast_node->prightchild);
				return ;
			}
			postorder_travel_ast(ast_node->prightchild);
		}
	}
	return ; 
}

void	postorder_travel_command(t_astnode *cmdnode)
{
	if (cmdnode)
	{
		// reds
		dup2(STDOUT_FILENO, 100);
		postorder_travel_reds(cmdnode->pleftchild);
		
		// args
		if(cmdnode->prightchild->prightchild->pvalue_index)
			exec_cmd(cmdnode->prightchild);
		dup2(100, STDOUT_FILENO);
	}
	return ; 

}

void	postorder_travel_reds(t_astnode *reds_node)
{
	// red
	if (reds_node->pleftchild)
	{
		goto_redirection(reds_node->pleftchild);
		//dup2(STDOUT_FILENO, 1);
		//dup2(STDIN_FILENO, 0);
	}
	// reds
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
	red = data->plexer->pptokens[red_node->pleftchild->pvalue_index[0]];
	filename = data->plexer->pptokens[red_node->prightchild->pvalue_index[0]];
	if(ft_strncmp(red, "<", -1)) // 타입이 어떤 타입으로 확인해야할지 잘 모르겠음ㅜㅇ ㅜ
		in_red(filename);
	else if(ft_strncmp(red,">", -1))
		out_red(filename);
	else if(ft_strncmp(red,">>", -1))
		append_red(filename);
	else if(ft_strncmp(red,"<<", -1))
		heredoc(filename);
}
