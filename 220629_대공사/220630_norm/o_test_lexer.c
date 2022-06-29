/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_test_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:44:47 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 03:21:05 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static int	get_type(char *value);
static void	type_word_to_cmd(int *i, int *command_flag);
static void	type_pipe(int *command_flag);
static int	word_to_option(int *i, int *command_flag);

void	lexical_analysis(void)
{
	int		i;
	int		command_flag;

	i = -1;
	command_flag = FALSE;

	// ft_calloc 후 할당 실패시 free 하는 함수 만들기
	data.lexer.ptype = (int *)ft_calloc(data.tokens_cnt + 1, sizeof(int));
	if (!data.lexer.ptype)
	/*
	error
	*/
		return ;
	while (data.lexer.pptokens[++i])
	{
		data.lexer.ptype[i] = get_type(data.lexer.pptokens[i]);
		if (data.lexer.ptype[i] == T_WORD)
			type_word_to_cmd(&i, &command_flag);
		if (data.lexer.ptype[i] == T_PIPE)
			type_pipe(&command_flag);
		else if (data.lexer.ptype[i] == T_REDIRECTION)
		{
			data.redirection_cnt++;
			if (ft_strncmp("<<", data.lexer.pptokens[i], -1))
				data.heredoc_cnt++;
		}
		else if (data.lexer.ptype[i] == T_WORD)
		{
			if (word_to_option(&i, &command_flag) == FALSE)
				return ;
		}
	}
}

static int	get_type(char *value)
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
		type = get_type(value);
		if (type == T_PIPE || type == T_REDIRECTION || type == T_ENV)
			type = T_WORD;
	}
	else
		type = T_WORD;
	return (type);
}

static void	type_word_to_cmd(int *i, int *command_flag)
{
	int	*type;

	type = data.lexer.ptype;
	if (*i == 0)
	{
		type[*i] = T_COMMAND;
		*command_flag = TRUE;
	}
	else if (*i != 0 && type[*i - 1] == T_PIPE)
	{
		type[*i] = T_COMMAND;
		*command_flag = TRUE;
	}
	else if (*command_flag == FALSE && type[*i - 2] == T_REDIRECTION)
	{
		type[*i] = T_COMMAND;
		*command_flag = TRUE;
	}
}

static int	word_to_option(int *i, int *command_flag)
{
	int		*type;
	char	**tokens;

	type = data.lexer.ptype;
	tokens = data.lexer.pptokens;
	if (i != 0 && type[*i - 1] == T_COMMAND)
	{
		if (is_option(tokens[*i]))
			type[*i] = T_OPTION;
	}
	if (is_env(tokens[*i]))
	{
		replace_env_to_value(*i);
		if (!data.lexer.pptokens[*i])
		{
			/*
			 error
			 */
			data.exit_status = 1;
			return (FALSE);
		}
	}
	return (TRUE);
}

static void	type_pipe(int *command_flag)
{
	data.pipe_cnt++;
	*command_flag = FALSE;
}
