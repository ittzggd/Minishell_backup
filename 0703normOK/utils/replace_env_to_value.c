/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_to_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:12:31 by hejang            #+#    #+#             */
/*   Updated: 2022/07/03 18:57:50 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_env(char	*token, int i, int *j);
static char	*get_value_from_envvlist(char *token, int j, int key_len);

void	replace_env_to_value(int i)
{
	char	*token;
	char	*argv;
	int		j;
	int		key_len;

	token = g_data.lexer.pptokens[i];
	j = 0;
	if (check_env(token, i, &j) == TRUE)
		return ;
	key_len = 0;
	while (token[j + key_len])
	{
		if (!ft_is_alpha(token[j + key_len]) && (token[j + key_len] != '_') \
			&& !ft_is_digit(token[j + key_len]) && (token[j + key_len] != '?'))
			break ;
		key_len++;
	}
	argv = get_value_from_envvlist(token, j, key_len);
	if (token[j + key_len] == '\0')
		g_data.lexer.pptokens[i] = argv;
	else
		g_data.lexer.pptokens[i] = ft_strjoin(argv, &token[j + key_len]);
	if (token)
		free(token);
}

static char	*get_value_from_envvlist(char *token, int j, int key_len)
{
	char	*key;
	char	*argv;

	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		ft_error("replace_env_to_value : allocation failed\n");
	ft_strlcpy(key, &token[j], key_len + 1);
	argv = get_envv(key);
	if (key)
		free(key);
	return (argv);
}

static int	check_env(char	*token, int i, int *j)
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
