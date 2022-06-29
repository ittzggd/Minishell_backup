/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_test_tokenize_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:22:36 by hejang            #+#    #+#             */
/*   Updated: 2022/06/29 23:22:49 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

char	*tokenize_input(char *input)
{
	int		split_index;

	if (!input)
		return (NULL);
	data.tokens_cnt = ft_wordcount(input); // 1. 단어 개수 세기
	if (data.tokens_cnt == ERROR)
		return (NULL);
	data.lexer.pptokens = (char **)malloc(sizeof(char *) * (data.tokens_cnt + 1));
	if (!data.lexer.pptokens)
		return (NULL); // 2. data.tokens malloc => NULL 체크
	split_index = ft_split_str((char *)input, data.lexer.pptokens);
	if (split_index != data.tokens_cnt)
	{
	 	ft_free_all(data.lexer.pptokens);
		data.lexer.pptokens = NULL;
	}
	// int k = 0;
	// while (data.lexer.pptokens[k])
	// {
	// 	printf("in tokenize__tokens[%d] : %s\n", k, data.lexer.pptokens[k]);
	// 	k++;
	// }
	return ("SUCCESS");
}


// int main()
// {
// 	char *str;
// 	int 	i = 0;

// 	str = "echo hi";
// 	data = ft_calloc(1, sizeof(t_data));
// 	tokenize_input(data, "echo hi");
// 	while(data.lexer.pptokens[i])
// 	{
// 		printf("pptokens[%d] : %s\n", i, data.lexer.pptokens[i]);
// 		i++;
// 	}
// }
