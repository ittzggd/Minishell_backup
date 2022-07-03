/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:53:00 by hejang            #+#    #+#             */
/*   Updated: 2022/07/03 21:46:54 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_argv(int cnt, t_astnode *argsnode)
{
	t_astnode	*argnode;
	char		**argv;
	int			i;

	i = 0;
	argnode = argsnode->prightchild;
	argv = (char **)ft_calloc(cnt + 1, sizeof(char *));
	while (i < cnt)
	{
		argv[i] = remove_quote(g_data.lexer.pptokens[argnode->pvalue_index[i]]);
		i++;
	}
	return (argv);
}

void	command_not_found_error(char *cmd)
{
	ft_error_message("nanoshell : command not found : ", 1);
	ft_error_message(cmd, 1);
	ft_error_message("\n", 1);
	exit(g_data.exit_status);
}

char	**allocate_empty_str_in_filepath(void)
{
	char	**filepath;

	filepath = ft_calloc(2, sizeof(char *));
	if (!filepath)
		ft_error("allocate_empty_str_in_filepath : allocation failed\n");
	filepath[0] = ft_strdup("");
	filepath[1] = NULL;
	return (filepath);
}
