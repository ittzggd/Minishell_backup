/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:13 by yukim             #+#    #+#             */
/*   Updated: 2022/06/14 19:15:42 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd(t_data *data, t_astnode *args_node)
{
	char	*tmp;
	char	*dst_path;
	int		chdir_ret;
	int		idx;
	// cd - 경우를 추가해야 함

	data->exit_status = 0;
	tmp = data->plexer->pptokens[args_node->prightchild->pvalue_index[1]];
	idx = args_node->prightchild->pvalue_index[1];
	if (idx == END || ft_strncmp(tmp, "~", -1)) // cd  ||  cd ~
	{	// cd 만 입력되면 HOME으로 이동해야 함.
		dst_path = get_envv(data, "HOME");
		if (!dst_path)
		{
			printf("minishell : cd : %s : No such file or directory\n", tmp);
			data->exit_status = 1;
			return (data->exit_status); // exit_status 실패
		}
	}
	else // cd ./eee    cd ../zd   cd libft
		dst_path = remove_quote(tmp);
	chdir_ret = chdir(dst_path);
	if (chdir_ret == -1) // chdir 실패시
	{
		printf("minishell : cd : %s : No such file or directory\n", tmp);
		if (dst_path != tmp)
		{
			if(dst_path)
				free(dst_path);
		}
		data->exit_status = 1;
		return (data->exit_status);
	}
	update_pwd_oldpwd(data, "OLDPWD");
	update_pwd_oldpwd(data, "PWD");
	return (data->exit_status); // exit_status 성공
}

void	update_pwd_oldpwd(t_data *data, char *key)
{
	char	*value;
	char	*tmp;
	
	if (get_el_node(data->envv_list, key))
	{
		if (ft_strncmp(key, "OLDPWD", -1))
			value = get_envv(data, "PWD");
		else if (ft_strncmp(key, "PWD", -1))
		{
			tmp = get_envv(data, key);
			if (tmp)
				free(tmp);
			value = getcwd(NULL, 0);	
		}
		insert_envv(data, key, value, TRUE); // 고민고민
	}
}
