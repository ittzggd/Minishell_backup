/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:19:44 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 16:55:17 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	replace_quote_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->lexer.pptokens[i] != NULL)
	{
		if (data->lexer.ptype[i] == T_REDIRECTION)
		{
			i++;
			if (data->lexer.pptokens[i] == NULL)
				break ;
			if (ft_strncmp("<<", data->lexer.pptokens[i - 1], -1) == FALSE)
				rm_argument_quote(data, i);
		}
		else if (data->lexer.ptype[i] == T_WORD \
					|| data->lexer.ptype[i] == T_COMMAND)
			rm_argument_quote(data, i);
		i++;
	}
}

void	rm_argument_quote(t_data *data, int i)
{
	char	*tokens;
	char	*rm_quote;

	tokens = data->lexer.pptokens[i];
	rm_quote = remove_quote(tokens);
	data->lexer.pptokens[i] = rm_quote;
	free(tokens);
}
