/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:35 by yukim             #+#    #+#             */
/*   Updated: 2022/06/29 23:23:05 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

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
		// if (init_flag == ERROR)  :: calloc -1 =>  exit
		// {
		// 	data.exit_status = 1;
		// 	i++;
		// 	continue ;
		// }
		if (is_valid_env(key) == ERROR)
		{
			ft_error_message("nanoshell: export: ", 1);
			ft_error_message(key, 1);
			ft_error_message(": not a valid identifier\n", 1);
			i++; // added
			continue ; // added
		}
		else if (is_valid_env(key) == TRUE)
		{
			insert_envv(key, value, init_flag);
			if (!value)
				continue ;
			else
			{
				if(key)
					free(key);
				if(value)
					free(value);
			}
		}
		i++;
	}
	return (data.exit_status);
}
