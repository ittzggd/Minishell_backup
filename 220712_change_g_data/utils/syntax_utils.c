/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:08:14 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 16:49:35 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	syntax_check_command(t_data *data, int *curr)
{
	int	*type;
	int	prev;

	type = data->lexer.ptype;
	prev = *curr - 1;
	if (*curr != 0 && (type[prev] == T_REDIRECTION || type[prev] == T_OPTION \
			|| type[prev] == T_COMMAND))
		type[*curr] = T_WORD;
}

void	syntax_check_redirection(t_data *data, int *curr, int *ret_status)
{
	int		*type;
	int		prev;

	type = data->lexer.ptype;
	prev = *curr - 1;
	if (type[*curr + 1] != T_WORD \
			|| (*curr != 0 && (type[prev] == T_REDIRECTION)))
		syntax_error(ret_status);
}

void	syntax_check_pipe(t_data *data, int *curr, int *ret_status)
{
	int		*type;
	int		prev;

	prev = *curr - 1;
	type = data->lexer.ptype;
	if ((type[*curr + 1] != T_COMMAND && type[*curr + 1] != T_REDIRECTION) \
			|| (*curr != 0 && type[prev] == T_REDIRECTION))
		syntax_error(ret_status);
}

void	syntax_check_null(t_data *data, int *curr, int *ret_status)
{
	int		*type;
	int		prev;

	prev = *curr - 1;
	type = data->lexer.ptype;
	if (*curr != 0 && (type[prev] == T_REDIRECTION || type[prev] == T_PIPE))
	{
		ft_error_message("NULL_ERROR\n", 1);
		*ret_status = 0;
	}
}
