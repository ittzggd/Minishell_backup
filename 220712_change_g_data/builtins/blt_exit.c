/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:05 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 19:19:00 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exit_status_argc_error(void);

void	ft_exit(t_data *data, t_astnode *args_node)
{
	int		cnt;
	char	*str;

	cnt = 0;
	g_exit_status = 0;
	while (args_node->prightchild->pvalue_index[cnt] != -1)
		cnt++;
	printf("exit\n");
	if (cnt >= 2)
	{
		str = data.lexer.pptokens[args_node->prightchild->pvalue_index[1]];
		g_exit_status = ft_atoi(str, args_node->prightchild);
		if (cnt > 2)
		{
			g_exit_status = exit_status_argc_error();
			return ;
		}
	}
	exit(g_exit_status);
}

void	exit_status_numeric_error(t_astnode *args_node)
{
	char	*str;

	str = data.lexer.pptokens[args_node->pvalue_index[1]];
	ft_error_message("exit: minishell: ", 255);
	ft_error_message(str, 255);
	ft_error_message(": numeric argument required", 255);
	exit(255);
}

static int	exit_status_argc_error(void)
{
	ft_error_message("minishell: exit :too many arguments\n", 1);
	return (1);
}
