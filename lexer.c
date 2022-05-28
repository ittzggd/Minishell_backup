/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:10:59 by yukim             #+#    #+#             */
/*   Updated: 2022/05/28 11:18:20 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if(type == T_PIPE || type == T_REDIRECTION)
			type = T_WORD;
	}
	else
		type = T_WORD;
	return (type);
}

t_lexer	*lexical_analysis(char **tokens)
{
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
