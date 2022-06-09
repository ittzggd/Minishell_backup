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
	char	*dst_path;
	int		chdir_ret;

	data->exit_status = 0;
	tmp = data->plexer->pptokens[args_node->pvalue_index[1]];
	if (tmp == -1 || ft_strncmp(tmp, "~", -1)) // cd  ||  cd ~
	{	// cd 만 입력되면 HOME으로 이동해야 함.
		dst_path = get_envv(data, "HOME");
		if (!dst_path)
		{
			// ERROR 출력 : setting Home path 어쩌구
			data->exit_status = 1;
			return (data->exit_status); // exit_status 실패
		}
	}
	else // cd ./eee    cd ../zd   cd libft
		dst_path = remove_quote(tmp);
	
	chdir_ret = chdir(dst_path);
	if (chdir_ret == -1) // chdir 실패시
	{
		// error message
		if (dst_path != tmp)
			free(dst_path);
		data->exit_status = 1;
	}
	
	return (data->exit_status) // exit_status 성공
}
