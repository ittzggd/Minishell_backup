/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_to_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:12:31 by hejang            #+#    #+#             */
/*   Updated: 2022/07/11 14:36:00 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	check_env(char	*token, int i, int *j);
// static char	*get_value(char *token, int j, int key_len);

// void	replace_env_to_value(int i)
// {
// 	char	*token;
// 	char	*argv;
// 	int		j;
// 	int		key_len;

// 	token = g_data.lexer.pptokens[i];
// 	j = 0;
// 	if (check_env(token, i, &j) == TRUE)
// 		return ;
// 	key_len = ft_key_len(token, j);
// 	argv = get_value(token, j, key_len);
// 	if (token[j + key_len] == '\0')
// 		g_data.lexer.pptokens[i] = argv;
// 	else
// 	{
// 		g_data.lexer.pptokens[i] = ft_strjoin(argv, &token[j + key_len]);
// 		free(argv);
// 	}	
// 	if (token)
// 		free(token);
// }


// static int	check_env(char	*token, int i, int *j)
// {
// 	if (ft_strncmp(&token[*j], "$", -1))
// 		return (TRUE);
// 	else if (ft_strncmp(&token[*j], "$?", -1))
// 		return (TRUE);
// 	else if (ft_strncmp(g_data.lexer.pptokens[i - 1], "<<", -1))
// 		return (TRUE);
// 	return (FALSE);
// }

// static char	*get_value(char *token, int j, int key_len)
// {
// 	char	*key;
// 	char	*value;

// 	key = ft_calloc(key_len + 1, sizeof(char));
// 	if (!key)
// 		ft_error("replace_env_to_value : allocation failed\n");
// 	ft_strlcpy(key, &token[j], key_len + 1);
// 	value = get_envv(key);
// 	if (key)
// 		free(key);
// 	if (!value)
// 		value = ft_strdup("");
// 	return (value);
// }
