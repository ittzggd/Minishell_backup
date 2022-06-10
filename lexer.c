/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:10:59 by yukim             #+#    #+#             */
/*   Updated: 2022/05/31 18:39:318 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/*
	헤더파일 구조체랑 lexer 배열로 바꾸기  => tokens의 길이를 구조체에 저장해줌
	lexer 배열로 바꿔도 괜찮을 듯 => command는 무조건 맨 앞 아니면 pipe 다음임
	command의 위치를 안다? 그럼 option위치도 || argument위치도 바로 알 수 있음

	더 좋다
*/

static int	get_type(char *value)
{
	int	type;

	if (!value || *value == '\0')
		type = T_NULL;
	else if (is_pipe(value))
		type = T_PIPE;
	else if (is_redirection(value))
		type = T_REDIRECTION;
	else if (is_cmd(value))
		type = T_COMMAND;
	else if (is_option(value))
		type = T_OPTION;
	else if (is_quote(*value))
	{
		value++;
		type = get_type(value);
		if (type == T_PIPE || type == T_REDIRECTION || type == T_ENV)
			type = T_WORD;
	}
	else
		type = T_WORD;
	return (type);
}

void	lexical_analysis(t_data *data)
{
	char	**tokens;
	int		*type;
	int		i;

	i = 0;
	tokens = data->plexer->pptokens;
	data->plexer->ptype = (int *)ft_calloc(data->tokens_cnt + 1, sizeof(int));
	type = data->plexer->ptype;
	if (!type)
		return ;
	while (tokens[i])
	{
		type[i] = get_type(tokens[i]);
		if (type[i] == T_PIPE)
			data->pipe_cnt++;
		else if (type[i] == T_REDIRECTION)
			data->redirection_cnt++;
		else if (type[i] == T_WORD)
		{
			if (is_env(tokens[i]))
			{
				// $와 괄호를 제외한 key값을 tokens[i]에 저장하기
				replace_env_to_value(i, data);
				if (!data->plexer->pptokens[i])
				{
					data->exit_status = 1;
					return ;
				}
				// 에러처리를 함수 쪼갤때 해주기
			}
		}
		i++;
	}
}
