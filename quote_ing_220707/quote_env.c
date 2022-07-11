/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:19:44 by yukim             #+#    #+#             */
/*   Updated: 2022/07/11 14:44:03 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static int	get_command_len(int i, int *quote);
static void	copy_command(char *rm_quote, char *tokens, int *quote, int len);

void	replace_quote_env(void)
{
	int		i;

	i = 0;
	while (g_data.lexer.pptokens[i] != NULL)
	{
		if (g_data.lexer.ptype[i] == T_COMMAND)
			rm_command_quote(i);
		else if (g_data.lexer.ptype[i] == T_REDIRECTION)
		{
			i++;
			if (g_data.lexer.pptokens[i] == NULL)
				break ;
			rm_command_quote(i);
		}
		else if (g_data.lexer.ptype[i] == T_WORD)
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
	len = get_command_len(i, &quote);
	rm_quote = ft_calloc(len + 1, sizeof(char));
	copy_command(rm_quote, tokens, &quote, 0);	
	g_data.lexer.pptokens[i] = rm_quote;
	free(tokens);
}

void	rm_argument_quote(int i)
{
	char	*tokens;
	// char	*tmp;
	char	*rm_quote;

	tokens = g_data.lexer.pptokens[i];
	// tmp = g_data.lexer.pptokens[i];
	rm_quote = remove_quote(tokens);
	g_data.lexer.pptokens[i] = rm_quote;
	// free(tmp);
	free(tokens);
}

static int	get_command_len(int i, int *quote)
{
	char	*tokens;
	int		len;
	int		idx;

	tokens = g_data.lexer.pptokens[i];
	len = 0;
	idx = 0;
	while(tokens[idx] != '\0')
	{
		*quote = is_quote(tokens[idx]);
		if (*quote && tokens[idx])
		{
			idx++;
			while (tokens[idx] && *quote != is_quote(tokens[idx]))
			{
				len++;
				idx++;
			}
		}
		else
			len++;
		idx++;
	}
	return (len);
}

static	void	copy_command(char *rm_quote, char *tokens, int *quote, int len)
{
	int	idx;

	idx = 0;
	while (tokens[idx] != '\0')
	{
		*quote = is_quote(tokens[idx]);
		if (*quote && tokens[idx])
		{
			idx++;
			while (tokens[idx] && *quote != is_quote(tokens[idx]))
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
}
