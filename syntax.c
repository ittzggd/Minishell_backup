/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 08:51:50 by yukim             #+#    #+#             */
/*   Updated: 2022/05/30 11:08:08 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_first_position(t_lexer *prev)
{
	return (!prev->type && !prev->value);
}

void	syntax_analysis(t_data *data)
{
	t_lexer *curr;
	t_lexer *prev;

	curr = data->lexer->plink; // 1st Pos
	prev = data->lexer; //dummy
	while(curr)
	{
		if(curr->type == T_COMMAND)
		{
			if (prev->type == T_REDIRECTION || prev->type == T_OPTION || prev->type == T_COMMAND)
				curr->type == T_WORD;
		}
		else if(curr->type == T_OPTION)
		{
			if ((prev->type == T_COMMAND && !ft_strncmp(curr->value, "echo", ft_strlen(curr->value)))
				|| prev->type != T_COMMAND)
			{
				//error
			}
		}
		else if(curr->type == T_REDIRECTION)
		{
			if(prev->type == T_PIPE || prev->type == T_REDIRECTION)
			{
				// ERROR;
			}
		}
		else if (is_first_position(prev)) //
		{
			//error => command not found	
		}
		else if (curr->type == T_PIPE)
		{
			if(curr->plink->type != T_COMMAND || prev->type == T_REDIRECTION)
			{
				// ERROR
			}
		}
		// else if (curr->type == T_WORD)
		// {
			
		// }
		else if (curr->type == T_NULL)
		{
			if(prev->type == T_REDIRECTION || prev->type == T_PIPE)
			{
				//error
			}
		}
		curr = curr->plink;
		prev = prev->plink;
	}
}