/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_test_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:07:44 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 05:59:44 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	syntax_analysis(void)
{
	int		curr;
	int		ret_status;

	curr = 0;
	ret_status = 0;
	while (curr < data.tokens_cnt)
	{
		if (data.lexer.ptype[curr] == T_COMMAND)
			syntax_check_command(&curr);
		else if (data.lexer.ptype[curr] == T_OPTION)
			syntax_check_option(&curr, &ret_status);
		else if (data.lexer.ptype[curr] == T_REDIRECTION)
			syntax_check_redirection(&curr, &ret_status);
		else if (curr == 0)
			syntax_error(&ret_status);
		else if (data.lexer.ptype[curr] == T_PIPE)
			syntax_check_pipe(&curr, &ret_status);
		else if (data.lexer.ptype[curr] == T_NULL)
			syntax_check_null(&curr, &ret_status);
		if (ret_status == 258)
			break ;
		curr++;
	}
	return (ret_status);
}

void	syntax_error(int *ret_status)
{
	// char *error_msg;
	
	// error_msg = ft_strdup("nanoshell: syntax error near unexpected token\n");
	// write(2, error_msg, ft_strlen(error_msg));
	// data.exit_status = 258;
	ft_error_message("nanoshell: syntax error near unexpected token\n", 258);
	*ret_status = 258;
}
