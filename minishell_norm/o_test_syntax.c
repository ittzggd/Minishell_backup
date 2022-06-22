/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_test_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:07:44 by hejang            #+#    #+#             */
/*   Updated: 2022/06/20 19:21:57 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	syntax_error(int *ret_status);
static void syntax_check_command(int *curr);
static void syntax_check_option(int *curr,  int *ret_status);
static void syntax_check_redirection(int *curr, int *ret_status);
static void syntax_check_pipe(int *curr,  int *ret_status);
static void syntax_check_null(int *curr,  int *ret_status);


int	syntax_analysis(void)
{
	int		curr;
	int		ret_status;
	
	curr = 0; 
	ret_status = 0;
	while(curr < data.tokens_cnt)
	{
		if(data.plexer->ptype[curr] == T_COMMAND)
			syntax_check_command(&curr);
		else if(data.plexer->ptype[curr] == T_OPTION)
			syntax_check_option(&curr, &ret_status);
		else if(data.plexer->ptype[curr] == T_REDIRECTION)
			syntax_check_redirection(&curr,  &ret_status);
		else if (curr == 0) //첫자리가 !CMD && !Redirection == ERROR
			syntax_error(&ret_status);
		else if (data.plexer->ptype[curr] == T_PIPE)
			syntax_check_pipe(&curr, &ret_status);
		else if (data.plexer->ptype[curr] == T_NULL)
			syntax_check_null(&curr, &ret_status);
		if(ret_status == 258)
			break;
		curr++;
	}
	return (ret_status);
}

static void	syntax_error(int *ret_status)
{
	printf("nanoshell: syntax error near unexpected token\n");
	*ret_status = 258;
}

static void syntax_check_command(int *curr)
{
	int	*type;
	int	prev;

	type = data.plexer->ptype;
	prev = *curr - 1;
	if (*curr != 0 && (type[prev] == T_REDIRECTION || type[prev] == T_OPTION 
		|| type[prev] == T_COMMAND))
		type[*curr] = T_WORD;
}


static void syntax_check_option(int *curr, int *ret_status)
{
	int		*type;
	char	**tokens;
	int		prev;

	type = data.plexer->ptype;
	tokens = data.plexer->pptokens;
	prev = *curr - 1;
	if (*curr != 0 && ((type[prev] == T_COMMAND && \
		!ft_strncmp(tokens[prev], "echo", -1)) || type[prev] != T_COMMAND))
		syntax_error(ret_status);
}

static void syntax_check_redirection(int *curr, int *ret_status)
{
	int		*type;
	int		prev;

	type = data.plexer->ptype;
	prev = *curr - 1;
	if (type[*curr + 1] != T_WORD  || (*curr != 0 && (type[prev] == T_REDIRECTION)))
				syntax_error(ret_status);
}

static void syntax_check_pipe(int *curr,  int *ret_status)
{
	int		*type;
	int		prev;

	prev = *curr - 1;
	type = data.plexer->ptype;
	if((type[*curr + 1] != T_COMMAND && type[*curr + 1] != T_REDIRECTION) 
		|| (*curr != 0 && type[prev] == T_REDIRECTION))
				syntax_error(ret_status);
}

static void syntax_check_null(int *curr,int *ret_status)
{
	int		*type;
	int		prev;

	prev = *curr - 1;
	type = data.plexer->ptype;
	if (*curr != 0 && (type[prev] == T_REDIRECTION || type[prev] == T_PIPE))
	{
		printf("null_ERROR\n");
		*ret_status = 0;
		//exit(0);
	}
}