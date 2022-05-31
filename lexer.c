/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:10:59 by yukim             #+#    #+#             */
/*   Updated: 2022/05/31 13:49:18 by hejang           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	헤더파일 구조체랑 lexer 배열로 바꾸기  => tokens의 길이를 구조체에 저장해줌
	lexer 배열로 바꿔도 괜찮을 듯 => command는 무조건 맨 앞 아니면 pipe 다음임
	command의 위치를 안다? 그럼 option위치도 || argument위치도 바로 알 수 있음

	더 좋다
*/

static int	get_type(char *value)
{
	int	type;

	/*
	5. not QUOTE str == word
	6. QUOTE str
		6-1. in quote str
		6-2. in quote cmd
		6-3. in quote option_flag
	7. option "-n" ?
	*/
	if (!value || *value == '\0') // Value 널가드 
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
		if (type == T_PIPE || type == T_REDIRECTION)
			type = T_WORD;
	}
	else
		type = T_WORD;
	return (type);
}

void	lexical_analysis(t_data *data)
{
	int		i;

	i = 0;
	dummy_header = ft_calloc(1, sizeof(t_lexer));
	if (!dummy_header)
		return (NULL);
	curr = dummy_header;
	while (tokens[i])
	{
		add_node = ft_calloc(1, sizeof(t_lexer));
		if (!add_node)
			retun (NULL);
		add_node->value = tokens[i];
		add_node->type = get_type(tokens[i]);
		if (add_node->type == T_PIPE)
			data->pipe_cnt++;
		else if (add_node->type == T_REDIRECTION)
			data->redirection_cnt++;
		curr->plink = add_node;
		curr = curr->plink;
		i++;
	}
	data->lexer = dummy_header;
}
