/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:22:36 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 14:35:52 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	analyze_input(char *input)
{
	if (tokenize_input(input) == ERROR)
		return (ERROR);
	lexical_analysis();
	if (syntax_analysis() != 0)
		return (ERROR);
	replace_quote_env();
	return (TRUE);
}

int	tokenize_input(char *input)
{
	int		split_index;

	g_data.tokens_cnt = ft_wordcount(input);
	if (g_data.tokens_cnt == ERROR)
	{
		g_data.exit_status = 258;
		return (ERROR);
	}
	g_data.lexer.pptokens = ft_calloc(g_data.tokens_cnt + 1, sizeof(char *));
	if (!g_data.lexer.pptokens)
		ft_error("tokenize_input : allocation failed\n");
	split_index = ft_split_str((char *)input, g_data.lexer.pptokens);
	if (split_index == ERROR)
		return (ERROR);
	return (TRUE);
}
