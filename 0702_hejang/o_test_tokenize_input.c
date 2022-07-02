/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_test_tokenize_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:22:36 by hejang            #+#    #+#             */
/*   Updated: 2022/07/02 20:58:37 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	tokenize_input(char *input)
{
	int		split_index;

	data.tokens_cnt = ft_wordcount(input);
	if (data.tokens_cnt == ERROR)
	{
		data.exit_status = 258;
		return (ERROR);
	}
	data.lexer.pptokens = ft_calloc(data.tokens_cnt + 1, sizeof(char *));
	if (!data.lexer.pptokens)
	{
		free_all_in_data();
		ft_error("tokenize_input : allocation error");
	}
	split_index = ft_split_str((char *)input, data.lexer.pptokens);
	if (split_index == ERROR)
		return (ERROR);
}
