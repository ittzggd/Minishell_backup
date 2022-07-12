/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:22:36 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 16:50:06 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	analyze_input(t_data *data, char *input)
{
	char	*replaced_str;

	replaced_str = replace_env_to_value(input);
	if (tokenize_input(data, replaced_str) == ERROR)
		return (ERROR);
	lexical_analysis(data);
	if (syntax_analysis(data) != 0)
		return (ERROR);
	replace_quote_env(data);
	return (TRUE);
}

int	tokenize_input(t_data *data, char *input)
{
	int		split_index;

	data->tokens_cnt = ft_wordcount(input);
	if (data->tokens_cnt == ERROR)
	{
		g_exit_status = 258;
		return (ERROR);
	}
	data->lexer.pptokens = ft_calloc(data->tokens_cnt + 1, sizeof(char *));
	if (!data->lexer.pptokens)
		ft_error("tokenize_input : allocation failed\n");
	split_index = ft_split_str((char *)input, data->lexer.pptokens);
	if (split_index == ERROR)
		return (ERROR);
	return (TRUE);
}
