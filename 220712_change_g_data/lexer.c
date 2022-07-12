/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:44:47 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 16:47:42 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	set_lexer_ptype(t_data *data);
static int	get_type(t_data *data, char *value);
static void	type_word_to_cmd(t_data *data, int *i, int *cmd_flag);
static void	word_to_option(t_data *data, int *i);

void	lexical_analysis(t_data *data)
{
	data->lexer.ptype = (int *)ft_calloc(data->tokens_cnt + 1, sizeof(int));
	if (!data->lexer.ptype)
		ft_error("lexical_analysis : allocation failed\n");
	set_lexer_ptype(data);
}

static void	set_lexer_ptype(t_data *data)
{
	int		i;
	int		command_flag;

	i = 0;
	command_flag = FALSE;
	while (data->lexer.pptokens[i])
	{
		data->lexer.ptype[i] = get_type(data, data->lexer.pptokens[i]);
		if (data->lexer.ptype[i] == T_WORD)
			type_word_to_cmd(data, &i, &command_flag);
		if (data->lexer.ptype[i] == T_PIPE)
		{
			data->pipe_cnt++;
			command_flag = FALSE;
		}
		else if (data->lexer.ptype[i] == T_REDIRECTION)
		{
			data->redirection_cnt++;
			if (ft_strncmp("<<", data->lexer.pptokens[i], -1))
				data->heredoc_cnt++;
		}
		else if (data->lexer.ptype[i] == T_WORD)
			word_to_option(data, &i);
		i++;
	}
}

static int	get_type(t_data *data, char *value)
{
	int	type;

	if (!value || *value == '\0')
		type = T_NULL;
	else if (is_pipe(value))
		type = T_PIPE;
	else if (is_redirection(value))
		type = T_REDIRECTION;
	else if (is_quote(*value))
	{
		value++;
		if (*value == '\0')
			return (T_WORD);
		else
			type = get_type(data, value);
		if (type == T_PIPE || type == T_REDIRECTION || type == T_ENV)
			type = T_WORD;
	}
	else
		type = T_WORD;
	return (type);
}

static void	type_word_to_cmd(t_data *data, int *i, int *cmd_flag)
{
	int	*type;

	type = data->lexer.ptype;
	if (*i == 0)
	{
		type[*i] = T_COMMAND;
		*cmd_flag = TRUE;
	}
	else if (*i != 0 && type[*i - 1] == T_PIPE)
	{
		type[*i] = T_COMMAND;
		*cmd_flag = TRUE;
	}
	else if (*cmd_flag == FALSE && (*i > 1) && type[*i - 2] == T_REDIRECTION)
	{
		type[*i] = T_COMMAND;
		*cmd_flag = TRUE;
	}
}

static void	word_to_option(t_data *data, int *i)
{
	int		*type;
	char	**tokens;

	type = data->lexer.ptype;
	tokens = data->lexer.pptokens;
	if (i != 0 && (type[*i - 1] == T_COMMAND || type[*i - 1] == T_OPTION))
	{
		if (is_option(tokens[*i]))
			type[*i] = T_OPTION;
	}
}
