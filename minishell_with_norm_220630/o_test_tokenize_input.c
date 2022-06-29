/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_test_tokenize_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:22:36 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 04:45:09 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

char	*tokenize_input(char *input)
{
	int		split_index;

	if (!input)
		return (NULL);
	data.tokens_cnt = ft_wordcount(input);
	if (data.tokens_cnt == ERROR)
	/*
		error
		*/
		return (NULL);
	data.lexer.pptokens = ft_calloc(data.tokens_cnt + 1, sizeof(char *));
	if (!data.lexer.pptokens)
	/*
		error
		*/
		return (NULL);
	split_index = ft_split_str((char *)input, data.lexer.pptokens);
	if (split_index != data.tokens_cnt)
	{
		ft_free_all(data.lexer.pptokens);
		data.lexer.pptokens = NULL;
	}
	return ("SUCCESS");
}
