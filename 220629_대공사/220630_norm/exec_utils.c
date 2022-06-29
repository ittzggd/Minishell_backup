/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:53:00 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 03:53:00 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./include/minishell.h"


char	**create_argv(int cnt, t_astnode *argsnode)
{
	t_astnode	*argnode;
	char		**argv;
	int			i;

	i = 0;
	argnode = argsnode->prightchild;
	argv = (char **)ft_calloc(i + 1, sizeof(char *));
	while (i < cnt)
	{
		argv[i] = ft_strdup(data.lexer.pptokens[argnode->pvalue_index[i]]);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void	command_not_found_error(char *cmd)
{
	ft_error_message("nanoshell : command not found : ", 1);
	ft_error_message(cmd, 1);
	ft_error_message("\n", 1);
	exit(data.exit_status);
}