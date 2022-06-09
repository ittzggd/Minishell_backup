/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:13 by yukim             #+#    #+#             */
/*   Updated: 2022/06/09 13:00:45 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd(t_data *data, t_astnode *args_node)
{
	char	*tmp;
	char	*dst_dir;

	tmp = data->plexer->pptokens[args_node->pvalue_index[1]];
	if (tmp == -1)
		return (TRUE);
	dst_dir = remove_quote(tmp);
	

}
