/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:07:44 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 16:49:10 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	syntax_analysis(t_data *data)
{
	int		curr;
	int		ret_status;

	curr = 0;
	ret_status = 0;
	while (curr < data->tokens_cnt)
	{
		if (data->lexer.ptype[curr] == T_COMMAND)
			syntax_check_command(data, &curr);
		else if (data->lexer.ptype[curr] == T_REDIRECTION)
			syntax_check_redirection(data, &curr, &ret_status);
		else if (curr == 0)
			syntax_error(&ret_status);
		else if (data->lexer.ptype[curr] == T_PIPE)
			syntax_check_pipe(data, &curr, &ret_status);
		else if (data->lexer.ptype[curr] == T_NULL)
			syntax_check_null(data, &curr, &ret_status);
		if (ret_status == 258)
			break ;
		curr++;
	}
	return (ret_status);
}

void	syntax_error(int *ret_status)
{
	ft_error_message("minishell: syntax error near unexpected token\n", 258);
	*ret_status = 258;
}
