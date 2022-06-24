/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/06/24 20:07:24 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	postorderTravelBinSTree(t_astnode *node);
void	free_data_lexer(void);
void	clear_linked_list(t_envv_node **p_list);
void	delete_linked_list(t_envv_node **p_list);
// 에러 처리 함수 만들기

void	postorderTravelBinSTree(t_astnode *node)
{
	int i = 0;

	if(node)
	{
		printf("node type : %d  ", node->nodetype);
		if(node->pvalue_index)
		{
			while(node->pvalue_index[i] != -1)
			{
				printf("       value : %s         ", data.lexer.pptokens[node->pvalue_index[i]]);
				i++;
			}
		}
		printf("\n");
		postorderTravelBinSTree(node->pleftchild);
		postorderTravelBinSTree(node->prightchild);
	}
}


int	analyze_input(char *input)
{
	tokenize_input(input); // data구조체 내부에 tokens 추가
	if (!data.lexer.pptokens) // data 모두 프리
		return (ERROR); // 에러 넘버 여러 경우로 나눌지 생각하기
	lexical_analysis();
	if (!data.lexer.ptype) // data Free
		return (ERROR); 
	if(syntax_analysis() != 0)
	{
		data.exit_status = 258;
		return (ERROR);
	}
	// parser
	return (TRUE);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*input_str;

	if (argc == 1)
	{
		init_setting(envp); 
		// 명령어 실행
		while (1)
		{	
			dup2(data.std_fd[0], STDIN_FILENO);
			dup2(data.std_fd[1], STDOUT_FILENO);
			input_str = readline("nanoshell >> ");
			if (input_str)
			{
				if (analyze_input(input_str) == ERROR)
				{
					free_data_lexer();
					continue ;
				}
				init_ast(); // ast 트리 생성
				// postorderTravelBinSTree(data.ast.prootnode);
				exec_ast(); // 명령어 실행 부분
				
			}
			else
				break ; //break가 없어야 할 듯 아마 우리는 ctrl+C가 아닌 이상 prompt를 계속 띄운 상태여야 함
			add_history(input_str);
			//free(input_str);

			// int k = 0;
			// while (data.lexer.pptokens[k])
			// {
			// 	printf("in main__tokens[%d] : %s\n", k, data.lexer.pptokens[k]);
			// 	k++;
			// }

			reset_data();
			// data에 있는 plexer free해주기
		}
		close(data.std_fd[0]);
		close(data.std_fd[1]);
	}
	//envv_list 랑 data만 free
	return (data.exit_status);
}

