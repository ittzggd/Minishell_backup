/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/06/29 14:23:53 by hejang           ###   ########.fr       */
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
				printf("       value : %s         ", data->lexer.pptokens[node->pvalue_index[i]]);
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
	if (!data->lexer.pptokens) // data 모두 프리
		return (ERROR); // 에러 넘버 여러 경우로 나눌지 생각하기
	lexical_analysis();
	if (!data->lexer.ptype) // data Free
		return (ERROR); 
	if(syntax_analysis() != 0)
	{
		data->exit_status = 258;
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
			// signal(SIGINT, &ctrl_c);
			// signal(SIGQUIT, &ctrl_bs);
			reset_signal();
			// // 리다이렉션이나 파이프를 거치면서 바뀐 STDIN, STDOUT 초기화
			// dup2(data->std_fd[0], STDIN_FILENO);
			// dup2(data->std_fd[1], STDOUT_FILENO);
			reset_stdfd();

			input_str = readline("nanoshell >> ");
			if (input_str)
			{
				if (analyze_input(input_str) == ERROR)
				{
					free_data_lexer();
					continue ;
				}
				init_ast(); // ast 트리 생성

				// heredoc 입력받기

				// postorderTravelBinSTree(data->ast.prootnode);
				exec_ast(); // 명령어 실행 부분
				
			}
			else // readline결과 NULL일 경우 == ctrl + d
			{
				// exit\n 출력 후 nanoshell 종료!!!
				// break ;

				//exit 되는데 커서 처리를 해줘야 할까???
				printf("exit\n");
				// free
					// data에 있는 모든 것 free.
				exit(0);
			}
			add_history(input_str);
			//free(input_str);

			// int k = 0;
			// while (data->lexer.pptokens[k])
			// {
			// 	printf("in main__tokens[%d] : %s\n", k, data->lexer.pptokens[k]);
			// 	k++;
			// }

			reset_data();
			// data에 있는 plexer free해주기
		}

		// 종료 전 열린 파이프 닫기
		close(data->std_fd[0]);
		close(data->std_fd[1]);
		// 종료 전 data에 남은 것들 free
		//envv_list 랑 data,,,,
	}
	return (data->exit_status);
}

