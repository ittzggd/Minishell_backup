#include "./include/minishell.h"



void	postorder_travel_ast(t_astnode *ast_node);

void	exec_cmd(t_astnode *argsnode)
{
	t_astnode	*argnode;
	char *blt_cmd;

	argnode = argsnode->prightchild;
	blt_cmd = data.plexer->pptokens[argnode->pvalue_index[0]];

	if (ft_strncmp(blt_cmd, "cd", -1))
		ft_cd(argsnode);
	else if (ft_strncmp(blt_cmd, "echo", -1))
		ft_echo(argsnode); 
	else if (ft_strncmp(blt_cmd, "env", -1))
		ft_env(FALSE);	// stdout에 출력하지 않고 dup2로 방향 바꿔서 써주기
	else if (ft_strncmp(blt_cmd, "exit", -1))
		ft_exit(argsnode);
	else if (ft_strncmp(blt_cmd, "export", -1))
		ft_export(argsnode);
	else if (ft_strncmp(blt_cmd, "pwd", -1))
		ft_pwd();
	else if (ft_strncmp(blt_cmd, "unset", -1))
		ft_unset(argsnode);
	else if (ft_strncmp(blt_cmd, "minishell", -1))
		printf("minishell hohoho\n");
	else
		printf("nanoshell : command not found : %s\n", blt_cmd);
}

// void	postorderTravelBinSTree(t_astnode *node)
// {
// 	int i = 0;

// 	if(node)
// 	{
// 		printf("node type : %d  ", node->nodetype);
// 		if(node->pvalue_index)
// 		{
// 			while(node->pvalue_index[i] != -1)
// 			{
// 				printf("       value : %s         ", data.plexer->pptokens[node->pvalue_index[i]]);
// 				i++;
// 			}
// 		}
// 		printf("\n");
// 		postorderTravelBinSTree(node->pleftchild);
// 		postorderTravelBinSTree(node->prightchild);
// 	}
// }


// int main()
// {
// 	//     <   : 뒤에온 파일명이 존재하는지만 알면 된다!

// 	int	fd; 
// 	//char	*str = "echo hhhh> a.txt > b.txt > c.txt | echo hi | > a.txt";
// 	//char	*str = "echo 'Hi > a.txt | pwd";
// 	//char 	*str = " << 'hihi'";
// 	char *str = "<< hihi";
// 	char *strr = "echo \"$test3\"hello";
// 	// t_astnode *filepath_node;
// 	char	*key;
// 	char	*value;

// 	data = ft_calloc(1, sizeof(t_data));

// 	key = "test1";
//  	value = "123";
//  	insert_envv(key, value,TRUE);
//  	key = "test2";
//  	value = "122222223";
//  	insert_envv(key, value,TRUE);
// 	key = "test3";
// 	value = "1233333333";
// 	insert_envv(key, value,TRUE);
	
	
// 	tokenize_input(strr);
// 	lexical_analysis();
// 	syntax_analysis();

// 	init_ast();
// 	//postorderTravelBinSTree(data.p_ast->prootnode);

// 	postorder_travel_ast(data.p_ast->prootnode);
//      //t_astnode *red_node = data.p_ast->prootnode->pleftchild->pleftchild;
//     // goto_redirection(red_node);


// 	return (0);
// }
