/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:20:55 by yukim             #+#    #+#             */
/*   Updated: 2022/06/03 15:00:54 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_input(t_data *data, char *input)
{
	int		split_index;

	if (!input)
		return (NULL);
	data->tokens_cnt = ft_wordcount(input); // 1. 단어 개수 세기
	if (data->tokens_cnt == ERROR)
		return (NULL);
	data->plexer->pptokens = (char **)malloc(sizeof(char *) * (data->tokens_cnt + 1));
	if (!data->plexer->pptokens)
		return (NULL); // 2. data->tokens malloc => NULL 체크
	split_index = ft_split_str((char *)input, data->plexer->pptokens);
	if (split_index != data->tokens_cnt)
	{
		ft_free_all(data->plexer->pptokens);
		data->plexer->pptokens = NULL;
	}
}

