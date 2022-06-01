/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:20:15 by hejang            #+#    #+#             */
/*   Updated: 2022/06/02 07:42:42 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// strdup 과 strjoin 가져오기
// ast완성 후, pptokes , ptype , plexer free?!?!

/*
			  pipe
		cmd			pipe
				cmd		cmd
*/
int	recur_pipe(t_astnode *ast_node, int index, t_data *data) // 가장 처음은 초기화된 rootNode, index = 0 이 들어옴
{
	char **tokens;
	int *type;
	int c_index;

	tokens = data->plexer->pptokens;
	type = data->plexer->ptype;
	c_index = index;
	while(tokens[index])
	{
		if (type[index] == T_PIPE)
		{
			ast_node->nodetype = A_PIPE;
			ast_node->pvalue = ft_strjoin("", tokens[index]); // 파이프 동가리 저장
			if (!ast_node->pvalue)
				return (ERROR);
			ast_node->pleftchild = insert_leftchildnode_ast(ast_node, A_COMMAND);
			tree_cmd(ast_node->pleftchild, c_index, data);
			ast_node->prightchild = insert_rightchildnode_ast(ast_node, 0);
			if (recur_pipe(ast_node->prightchild, index + 1, data))
				return(TRUE);
		}
		index++;
	}
//	if (tokens[index] == NULL) // 일단 주석
		ast_node->nodetype = A_COMMAND;
		tree_cmd(ast_node, c_index, data);
	return (TRUE);
}

// cmd 함수의 역할은 첫번째 리다이렉션을 만날때까지 탐색해서
// args   reds  트리 노드를 만드는 것이다
void	tree_cmd(t_astnode *ast_node, int index, t_data *data)
{
	char	**tokens;
	int		*type;

	if (ast_node->nodetype != A_COMMAND)
		return ;
	tokens = data->plexer->pptokens;
	type = data->plexer->ptype;
	//leftchild에 tree_reds 실행하는데, 첫번째 리다이렉션 만나면 A_REDS밑에 노드를 생성해야 함
	ast_node->pleftchild = insert_leftchildnode_ast(ast_node, 0);
	ast_node->prightchild = insert_rightchildnode_ast(ast_node, A_ARGUMENTS);
	tree_args(ast_node->prightchild, index, data);
	while (type[index] != T_PIPE && tokens[index])
	{
		if (type[index] = T_REDIRECTION)
		{
			ast_node->pleftchild->nodetype = A_REDIRECTIONS;
			tree_reds(ast_node->pleftchild, index, data);
			break ;
		}
		index++;
		// [T_redirect] [T_WORD] 다음에 ,오는 T_WORD는 ARG에 추가하기
	}
}


// args 밑부분 만들기
int	tree_args(t_astnode *ast_node, int index, t_data *data)
{
	char		*tmp;
	char		**tokens;
	int			*type;
	t_astnode	*args_leftchild;
	t_astnode	*args_rightchild;

	if (ast_node->nodetype != A_ARGUMENTS)
		return ;
	tokens = data->plexer->pptokens;
	type = data->plexer->ptype;
	args_leftchild = ast_node->pleftchild;
	args_rightchild = ast_node->prightchild;
	args_leftchild = insert_leftchildnode_ast(ast_node, A_FILEPATH);
	args_leftchild->pvalue = ft_strjoin("", tokens[index]);
	if (!args_leftchild->pvalue)
		return (ERROR);
	args_rightchild = insert_rightchildnode_ast(ast_node, A_ARGUMENT);
	args_rightchild->pvalue = ft_strjoin("", "");
	if(!args_rightchild->pvalue)
		return (ERROR);
	while (tokens[index] && type[index] != T_PIPE)
	{
		if (type[index] = T_REDIRECTION) // red filename
			index+=2;
		else
		{
			tmp = ft_strjoin(args_rightchild->pvalue, tokens[index]);
			free(args_rightchild->pvalue);
			if (!tmp)
				return (ERROR);
			args_rightchild->pvalue = tmp;
			index++;
		}
	}
	return (TRUE);
}
// reds 밑부분 만들기
void	tree_reds(t_astnode *ast_node, int index, t_data *data)
{
	char		**tokens;
	int			*type;
	t_astnode	*leftchild;
	t_astnode	*rightchild;
	
	if (ast_node->nodetype != A_REDIRECTIONS)
		return ;
	tokens = data->plexer->pptokens;
	type = data->plexer->ptype;
	leftchild = insert_leftchildnode_ast(ast_node, A_REDIRECTION); // RED
	rightchild = insert_rightchildnode_ast(ast_node, 0); // REDS
	if (type[index] == T_REDIRECTION)
	{
		// RED->leftchild, RED->Rightchild
		leftchild->pleftchild = insert_leftchildnode_ast(ast_node, A_REDIRECTION_TYPE);
		leftchild->prightchild = insert_rightchildnode_ast(ast_node, A_FILENAME);
		
		//A_REDIRECTION_TYPE 와 A_FILENAME 노드에 value 넣기 추가해야 함
		leftchild->pleftchild->pvalue = ft_strjoin("", tokens[index]);
		leftchild->prightchild->pvalue = ft_strjoin("", tokens[index + 1]);
	}
	index++;
	while (type[index] != T_PIPE && tokens[index])
	{
		if (type[index] == T_REDIRECTION)
		{
			rightchild->nodetype = A_REDIRECTIONS;
			tree_reds(rightchild, index, data);
			return ;
		}
		index++;
	}
}