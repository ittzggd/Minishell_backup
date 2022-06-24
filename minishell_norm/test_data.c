/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:31:33 by yukim             #+#    #+#             */
/*   Updated: 2022/06/24 20:09:06 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

t_data	data;

void	free_data_lexer(void)
{
	int	i;

	i = 0;
	data.tokens_cnt = 0;
	data.redirection_cnt = 0;
	data.pipe_cnt = 0;
	if (data.plexer)
	{
		if (data.plexer->ptype)
			free(data.plexer->ptype);
		while (data.plexer->pptokens[i])
		{
			if (data.plexer->pptokens[i])
			{
				free(data.plexer->pptokens[i]);
				data.plexer->pptokens[i] = NULL;
			}
			i++;
		}
		if (data.plexer->pptokens)
			free(data.plexer->pptokens);
		free(data.plexer);
	}
}

void	reset_data(void)
{
	free_data_lexer();
	if(data.p_ast)
		free_ast(data.p_ast);
}


void	free_data() // data  envv_lst포함 모두 FREE
{
	
}
