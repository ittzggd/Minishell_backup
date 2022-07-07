/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:19:44 by yukim             #+#    #+#             */
/*   Updated: 2022/07/07 19:19:44 by yukim            ###   ########.fr       */
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
	// char	*tmp;
	char	*rm_quote;
	int		len;
	int		idx;
	int		quote;

	tokens = g_data.lexer.pptokens[i];	
	// tmp = tokens;
	len = 0;
	idx = 0;
	while(tokens[idx] != '\0')
	{
		quote = is_quote(tokens[idx]);
		if (quote && tokens[idx])
		{
			idx++;
			while (tokens[idx] && quote != is_quote(tokens[idx]))
			{
				len++;
				idx++;
			}
		}
		else
			len++;
		idx++;
	}
	rm_quote = ft_calloc(len + 1, sizeof(char));
	idx = 0;
	len = 0;
	while(tokens[idx] != '\0')
	{
		quote = is_quote(tokens[idx]);
		if (quote && tokens[idx])
		{
			idx++;
			while (tokens[idx] && quote != is_quote(tokens[idx]))
			{
				rm_quote[len] = tokens[idx];
				len++;
				idx++;
			}
		}
		else
		{
			rm_quote[len] = tokens[idx];
			len++;
		}
		idx++;
	}
	rm_quote[len] = '\0';
	g_data.lexer.pptokens[i] = rm_quote;
	free(tokens);
	// free(tmp);
}

void	rm_argument_quote(int i)
{
	char	*tokens;
	char	*tmp;
	char	*rm_quote;

	tokens = g_data.lexer.pptokens[i];
	// tmp = g_data.lexer.pptokens[i];
	rm_quote = remove_quote(tokens);
	g_data.lexer.pptokens[i] = rm_quote;
	// free(tmp);
	free(tokens);
}


// char	*rm_quote(char *str_with_quote)
// {
	// int		quote_flag;
	// int		i;
	// int		idx;
	// int		len;
	// char	*rm_quote;
	// char	*tmp;

	// i = 0;
	// idx = 0;
	// len = 0;
	// while(str_with_quote[i])
	// {
	// 	if(is_quote(str_with_quote[i]) == FALSE))
	// 	{
	// 		while(str_with_quote[i] && is_quote(str_with_quote[i]) == FALSE)
	// 		{
	// 			len++;
	// 			i++;
	// 		}
	// 		rm_quote = ft_calloc(len + 1, sizeof(char));
	// 		rm_quote = ft_strlcpy(rm_quote, str_with_quote, len + 1);
	// 	}
	// 	if(str_with_quote[i] && is_quote(str_with_quote) != FALSE)
	// 	{
	// 		quote_flag = is_quote(str_with_quote[i]);
	// 		i++;
	// 		len = 0;
	// 		idx = i;
	// 		while(quote_flag != is_quote(str_with_quote[i])
	// 		{
	// 			len++;
	// 			i++;
	// 		}

	// 	}
	// }
//}
