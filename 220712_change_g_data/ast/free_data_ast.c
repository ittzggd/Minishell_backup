/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:30:35 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 16:38:20 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	free_data_ast(t_data *data)
{
	if (data->ast.prootnode)
	{
		delete_astnode(data->ast.prootnode);
		ft_bzero(&data->ast, sizeof(t_ast));
	}
}
