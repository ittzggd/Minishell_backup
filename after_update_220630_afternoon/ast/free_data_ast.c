/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_delete_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:30:35 by yukim             #+#    #+#             */
/*   Updated: 2022/07/01 03:30:35 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void free_data_ast(void)
{
	if (data.ast.prootnode)
	{
		delete_astnode(data.ast.prootnode);
		ft_bzero(&data.ast, sizeof(t_ast));
	}
}
