/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:31:33 by yukim             #+#    #+#             */
/*   Updated: 2022/06/15 20:26:23 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	data;

void	init_data() // data malloc
{
	// 헤더파일에 전역변수를 포인터가 아닌 t_data data로 바꾸기, 다른 함수들도 모두 ㅁㅐ개변수 수정 및 포인터참조 수정
}

void	free_data_lexer(void)
{
	int	i;

	i = 0;
	data.pipe_cnt = 0;
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
	//delete_linked_list(&data.envv_list);
	//data.exit_status = 0;
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
