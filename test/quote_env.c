/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:21:55 by hejang            #+#    #+#             */
/*   Updated: 2022/07/07 14:15:57 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
void	rm_command_quote(int i);

void	rm_argument_quote(int i);

void	replace_quote_env()
{
	int		i;

	i = 0;
	while(g_data.lexer.pptokens[i] != NULL)
	{
		if(g_data.lexer.ptype[i] == T_COMMAND)
			rm_command_quote(i);
		else if(g_data.lexer.ptype[i] == T_WORD)
			rm_argument_quote(i);
		i++;
	}
}

void	rm_command_quote(int i)
{
	char	*tokens;
	char	*tmp;
	char	*rm_quote;
	int		len;
	int		idx;

	tokens = g_data.lexer.pptokens[i];	
	tmp = tokens;
	len = 0;
	idx = 0;
	while(tokens[idx] != '\0')
	{
		if(tokens[idx] != '\"' && tokens[idx] != '\'')
			len++;
		idx++;
	}
	rm_quote = ft_calloc(len + 1, sizeof(char));
	idx = 0;
	len = 0;
	while(tokens[idx] != '\0')
	{
		if(tokens[idx] != '\"' && tokens[idx] != '\'')
		{
			rm_quote[len] = tokens[idx];
			len++;
		}	
		idx++;
	}
	rm_quote[len] = '\0';
	g_data.lexer.pptokens[i] = rm_quote;
	free(tmp);
}

void	rm_argument_quote(int i)
{
	char	*tokens;
	char	*tmp;
	char	*rm_quote;

	tokens = g_data.lexer.pptokens[i];
	tmp = g_data.lexer.pptokens[i];
	rm_quote = remove_quote(tokens);
	g_data.lexer.pptokens[i] = rm_quote;
	free(tmp);
}


char	*rm_quote(char *str_with_quote)
{
	int		quote_flag;
	int		i;
	int		idx;
	int		len;
	char	*rm_quote;
	char	*tmp;

	i = 0;
	idx = 0;
	len = 0;
	quote_flag = is_quote(str_with_quote[i]);
	while(str_with_quote[i])
	{
		if(quote_flag == FALSE)
		{
			while(quote_flag == FALSE)
			{
				
			}
		}
	}
}


