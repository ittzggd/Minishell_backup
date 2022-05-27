/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:10:59 by yukim             #+#    #+#             */
/*   Updated: 2022/05/27 19:10:59 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd(char *value)
{
	char	*cmd[];

	cmd = 
	if(ft_strncmp(value, cmd, ft_strlen(value)))
		return (TRUE);
	return (FALSE);
}

static int	get_type(char *value)
{
	int	type;

	/*
	4. CMD? => strcmp로 일일이 비교
	5. not QUOTE str == word
	6. QUOTE str
		6-1. in quote str
		6-2. in quote cmd
	7. flag 처리 고민
	*/
	if (!value)
		type = T_NULL;
	else if (is_pipe(value))
		type = T_PIPE;
	else if (is_redirection(value))
		type = T_REDIRECTION;
	else if (is_cmd(value))
		type = T_COMMAND;
	return (type);
}

t_lexer	*lexical_analysis(char **tokens)
{
	/*
	1. t_lexer 구조체 calloc => NULL 체크
	2. t_lexer->value = tokens[i] 복사
	3. t_lexer->type 정하기
	4. t_lexer->pLink 연결
	5. 에러 예외 처리

	7. 반환
	*/
	t_lexer	*dummy_header;
	t_lexer	*curr;
	t_lexer	*add_node;
	int		i;

	i = 0;
	dummy_header = ft_calloc(1, sizeof(t_lexer));
	if (!dummy_header)
		return (NULL);
	curr = dummy_header;
	while(tokens[i])
	{
		add_node = ft_calloc(1, sizeof(t_lexer));
		if(!add_node)
			retun (NULL);
		add_node->value = tokens[i];
		add_node->type = get_type(tokens[i]);
		curr->plink = add_node;
		curr = curr->plink;	
		i++;	
	}
	return (dummy_header);
}
