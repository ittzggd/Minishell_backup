/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:41 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 19:22:16 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static int	is_prev_pipe__ft_unset_util(t_data *data, t_astnode *args_node);
static void	ft_unset_with_args(t_data *data, t_astnode *args_node);

int	ft_unset(t_data *data, t_astnode *args_node)
{
	g_exit_status = 0;
	if (args_node->prightchild->pvalue_index[1] == END)
		return (g_exit_status);
	ft_unset_with_args(data, args_node);
	return (g_exit_status);
}

static void	ft_unset_with_args(t_data *data, t_astnode *args_node)
{
	int			i;
	char		*key;
	t_envv_node	*env_node;

	i = 1;
	while (args_node->prightchild->pvalue_index[i] != END)
	{
		key = data->lexer.pptokens[args_node->prightchild->pvalue_index[i]];
		env_node = get_el_node(data->envv_list, key);
		if (!env_node)
			g_exit_status = 1;
		else
		{
			if (is_prev_pipe__ft_unset_util(data, args_node) == TRUE)
				return ;
			remove_ll_element(data, &data->envv_list, env_node->key);
		}
		i++;
	}
}

static int	is_prev_pipe__ft_unset_util(t_data *data, t_astnode *args_node)
{
	int	position;

	position = args_node->prightchild->pvalue_index[0] - 1;
	if (position < 0)
		return (FALSE);
	if (data->lexer.ptype[position] == T_PIPE)
		return (TRUE);
	return (FALSE);
}
