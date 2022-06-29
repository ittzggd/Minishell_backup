/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:05 by yukim             #+#    #+#             */
/*   Updated: 2022/06/28 18:47:54 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exit_status_argc_error(t_astnode *args_node);

void	ft_exit(t_astnode *args_node)
{
	int		cnt;
	char	*str;
	
	cnt = 0;
	data->exit_status = 0;
	while (args_node->prightchild->pvalue_index[cnt] != -1)
		cnt++;
	printf("exit\n");
	if(cnt >= 2)
	{
		str = data->lexer.pptokens[args_node->prightchild->pvalue_index[1]];
		data->exit_status = ft_atoi(str, args_node->prightchild);
		printf("ft_exit str : %s\n", str);
		printf("ft_exit str => data->exit_status : %d\n", data->exit_status);
		if(cnt > 2)
		{
			data->exit_status = exit_status_argc_error(args_node->prightchild);
			return ;
		}
	}
	exit(data->exit_status);
}

void	exit_status_numeric_error(t_astnode *args_node)
{
	char *str;

	str = data->lexer.pptokens[args_node->pvalue_index[1]];
	printf("exit: minishell: %s: ", str);
	printf("numeric argument required");
	exit(255);
}
static int	exit_status_argc_error(t_astnode *args_node)
{
	printf("minishell: exit :too many arguments\n");
	return (1);
}
