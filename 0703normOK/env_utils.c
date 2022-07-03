/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:12:31 by hejang            #+#    #+#             */
/*   Updated: 2022/07/03 17:16:32 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	check_env(char	*token, int i, int *j)
{
	if (ft_strncmp(&token[*j], "$", -1))
		return (TRUE);
	else if (token[*j] && (token[*j] == '$' && token[*j + 1] == '\"'))
	{
		g_data.lexer.pptokens[i] = remove_quote(&token[*j + 1]);
		if (token)
			free(token);
		return (TRUE);
	}
	else if (ft_strncmp(&token[*j], "\"$\"", 3))
	{
		g_data.lexer.pptokens[i] = remove_quote(&token[*j]);
		if (token)
			free(token);
		return (TRUE);
	}
	else if (ft_strncmp(&token[*j], "$?", -1))
		return (TRUE);
	else if (ft_strncmp(g_data.lexer.pptokens[i - 1], "<<", -1))
		return (TRUE);
	while (token[*j] && (token[*j] == '$'\
		|| (token[*j] == '\"' && token[*j + 1] == '$')))
		(*j)++;
	return (FALSE);
}

void	get_value(char *key, char *token, int key_len, int i, int j)
{
	char	*argv;

	ft_strlcpy(key, &token[j], key_len + 1);
	argv = get_envv(key);
	if (key)
		free(key);
	if (token[j + key_len] == '\0')
		g_data.lexer.pptokens[i] = argv;
	else
		g_data.lexer.pptokens[i] = ft_strjoin(argv, &token[j + key_len]);
	if (token)
		free(token);
}
