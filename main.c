/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/06/09 19:29:59 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// 에러 처리 함수 만들기

int	analyze_input(char *input)
{
	tokenize_input(data, input); // data구조체 내부에 tokens 추가
	if (!data->plexer->pptokens) // data 모두 프리
		return (ERROR); // 에러 넘버 여러 경우로 나눌지 생각하기
	lexical_analysis(data);
	if (!data->plexer->ptype) // data Free
		return (ERROR); 
	syntax_analysis(data);
	// parser
}

int	main(int argc, char *argv[], char **envp)
{
	char	*input_str;
	char	*key;
	char	*value;

	if(argc == 1)
	{
		while (*envp)
		{
			init_envp(*envp, &key, &value);
			insert_envv(data, key, value);
		}
		insert_envv(data, "OLDPWD", NULL);
		while (1)
		{
			input_str = readline("nanoshell >> ");
			if (input_str)
			{
				if (analyze_input(input_str) == ERROR)
					continue ;
				// 명령어 실행 부분
			}
			else
				break ; //break가 없어야 할 듯 아마 우리는 ctrl+C가 아닌 이상 prompt를 계속 띄운 상태여야 함
			add_history(input_str);
			free(input_str);
		}
	}
	return (data->exit_status);
}
