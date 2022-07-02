/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:35 by yukim             #+#    #+#             */
/*   Updated: 2022/07/02 18:20:56 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static void init_variables_ft_export(int *index, char **input, int *init_flag);

int	ft_export(t_astnode *args_node)
{
	char	*input;
	char	*key;
	char	*value;
	char	*p_equal;
	int		init_flag;
	int		i;
	int		index;

	init_flag = FALSE;
	data.exit_status = 0;
	if (args_node->prightchild->pvalue_index[1] == END)
	{
		ft_env(TRUE);
		return (data.exit_status);
	}
	i = 1;
	while (args_node->prightchild->pvalue_index[i] != -1)
	{
		index = args_node->prightchild->pvalue_index[i];
		input = remove_quote(data.lexer.pptokens[index]);
		init_flag = init_envp(input, &key, &value);
		if (input != data.lexer.pptokens[index])
			free(input);
		if (is_valid_env(key) == ERROR)
		{
			ft_error_message("nanoshell: export: ", 1);
			ft_error_message(key, 1);
			ft_error_message(": not a valid identifier\n", 1);
		}
		else if (is_valid_env(key) == TRUE)
		{
			insert_envv(key, value, init_flag);
			if (!value)
				continue ;
		}
		i++;
	}
	return (data.exit_status);
}

static void init_variables_ft_export(int *index, char **input, int *init_flag)
