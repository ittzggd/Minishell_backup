/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/05/31 13:44:21 by hejang           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 에러 처리 함수 만들기

int	analyze_input(char *input)
{
	t_data		*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (ERROR);
	tokenize_input(data, input); // data구조체 내부에 tokens 추가
	if (!data->tokens)
		return (ERROR); // 에러 넘버 여러 경우로 나눌지 생각하기
	lexical_analysis(data);
	if (!data->lexer)
		return (ERROR);
	syntax_analysis(data);
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
