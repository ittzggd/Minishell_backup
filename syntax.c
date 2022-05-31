/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 08:51:50 by yukim             #+#    #+#             */
/*   Updated: 2022/05/31 22:09:26 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_analysis(t_data *data)
{
	int		curr;
	int		prev;
	int		*type;
	char	**tokens;
	
	curr = 0; 
	type = data->plexer->ptype;
	tokens = data->plexer->pptokens;
	while(curr < data->tokens_cnt)
	{
		prev = curr - 1;
		if(type[curr] == T_COMMAND)
		{
			if (curr != 0 && (type[prev] == T_REDIRECTION || type[prev] == T_OPTION || type[prev] == T_COMMAND))
				type[curr] == T_WORD;
		}
		else if(type[curr] == T_OPTION)
		{
			if (curr != 0 && ((type[prev] == T_COMMAND && !ft_strncmp(tokens[curr], "echo", ft_strlen(tokens[curr])))
				|| type[prev] != T_COMMAND))
			{
				//error
			}
		}
		else if(type[curr] == T_REDIRECTION)
		{
			if (curr != 0 && (type[prev] == T_PIPE || type[prev] == T_REDIRECTION))
			{
				// ERROR;
			}
		}
		else if (curr == 0) //첫자리가 !CMD && !Redirection == ERROR
		{
			//error => command not found	
		}
		else if (type[curr] == T_PIPE)
		{
			if(type[curr + 1] != T_COMMAND || (curr != 0 && type[prev] == T_REDIRECTION))
			{
				// ERROR
			}
		}
		// else if (type[curr] == T_WORD)
		// {
			
		// }
		else if (type[curr] == T_NULL)
		{
			if (curr != 0 && (type[prev] == T_REDIRECTION || type[prev] == T_PIPE))
			{
				//error
			}
		}
		
		curr++;
	}
}
