/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:31:33 by yukim             #+#    #+#             */
/*   Updated: 2022/06/27 19:13:41 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

t_data	data;

void	free_data_lexer(void)
{
	int	i;

	i = 0;
	if (data.lexer.ptype)
		free(data.lexer.ptype);
	if (data.lexer.pptokens)
	{
		while (data.lexer.pptokens[i])
		{
			free(data.lexer.pptokens[i]);
			i++;
		}
		free(data.lexer.pptokens);
	}
	ft_bzero(&data.lexer, sizeof(t_lexer));
}

void	reset_data(void)
{
	data.tokens_cnt = 0;
	data.redirection_cnt = 0;
	data.pipe_cnt = 0;
	data.p_flag = FALSE;
//	data.heredoc_flag = 0;
	free_data_lexer();
	free_data_ast();
}


void	free_data() // data  envv_lst포함 모두 FREE
{
	
}
