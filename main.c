/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/05/28 13:59:57 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 에러 처리 함수 만들기

int	analyze_input(char *input)
{
	char		**tokens;
	t_lexer		*lexer_tokens;

	tokens = tokenize_input(input);
	if(!tokens)
		return (ERROR); // 에러 넘버 여러 경우로 나눌지 생각하기
	lexer_tokens = lexical_analysis(tokens);
	if (!lexer_tokens)
		return (ERROR);
	// parser
}

int	main(void)
{
	char	*input_str;

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
	return (0);
}