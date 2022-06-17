/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:13 by yukim             #+#    #+#             */
/*   Updated: 2022/06/15 21:19:41 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd(t_astnode *args_node)
{
	char	*tmp;
	char	*rm_quote_tmp;
	char	*dst_path;
	char	*home_path;
	int		chdir_ret;
	int		idx;
	// cd - 경우를 추가해야 함

	data.exit_status = 0;
	tmp = data.plexer->pptokens[args_node->prightchild->pvalue_index[1]];
	rm_quote_tmp = remove_quote(tmp);
	idx = args_node->prightchild->pvalue_index[1];
	if (idx == END || ft_strncmp(rm_quote_tmp, "~", 1)) // cd  ||  cd ~
	{	// cd 만 입력되면 HOME으로 이동해야 함.
		home_path = get_envv(data, "HOME");
		dst_path = ft_strjoin(home_path, rm_quote_tmp + 1);
		if (!home_path)
		{
			printf("minishell : cd : %s : No such file or directory\n", dst_path);
			data.exit_status = 1;
			return (data.exit_status); // exit_status 실패
		}
	}
	else // cd ./eee    cd ../zd   cd libft
		dst_path = rm_quote_tmp;
	chdir_ret = chdir(dst_path);
	if (chdir_ret == ERROR) // chdir 실패시
	{
		printf("minishell : cd : %s : No such file or directory\n", tmp);
		data.exit_status = 1;
	}
	else
	{
		update_pwd_oldpwd("OLDPWD");
		update_pwd_oldpwd("PWD");
	}
	if (dst_path != rm_quote_tmp)
		free(dst_path);
	if (rm_quote_tmp != tmp)
		free(rm_quote_tmp);
	return (data.exit_status);
}

void	update_pwd_oldpwd(char *key)
{
	char	*value;
	char	*tmp;
	t_envv_node	*node;
	
	node = get_el_node(data.envv_list, key);
	if (node)
	{
		if (ft_strncmp(key, "OLDPWD", -1))
			value = get_envv("PWD");
		else if (ft_strncmp(key, "PWD", -1))
		{
			if (node->value)
			{
				free(node->value);
				node->value = NULL;
			}
			value = getcwd(NULL, 0);
	
		}
		insert_envv(key, value, TRUE); // 고민고민
	}
}
