/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:13 by yukim             #+#    #+#             */
/*   Updated: 2022/06/29 23:22:01 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	cd_home(char **home_path, char **dst_path, char **rm_quote_tmp);
static void	chdir_error(char *tmp);
static void	update_pwd(void);

int	ft_cd(t_astnode *args_node) // cd -경우 추가 바람
{
	char	*tmp;
	char	*rm_quote_tmp;
	char	*dst_path;
	char	*home_path;
	int		idx;

	data.exit_status = 0;
	tmp = data.lexer.pptokens[args_node->prightchild->pvalue_index[1]];
	rm_quote_tmp = remove_quote(tmp);
	idx = args_node->prightchild->pvalue_index[1];
	if (idx == END || ft_strncmp(rm_quote_tmp, "~", 1)) // cd  ||  cd ~
	{
		if(cd_home(&home_path, &dst_path, &rm_quote_tmp) == ERROR)
			return (data.exit_status);
	}
	else // cd ./eee    cd ../zd   cd libft
		dst_path = rm_quote_tmp;
	if (chdir(dst_path) == ERROR) // chdir 실패시
		chdir_error(tmp);
	else
		update_pwd();
	if (dst_path != rm_quote_tmp)  // rm_quote_str free함수 만들어서 빼기 
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


static int	cd_home(char **home_path, char **dst_path, char **rm_quote_tmp)
{
	*home_path = get_envv("HOME");
	*dst_path = ft_strjoin(*home_path, *rm_quote_tmp + 1);
	if (!home_path)
	{
		printf("minishell : cd : %s : No such file or directory\n", *dst_path);
		data.exit_status = 1;
		return (ERROR); // exit_status 실패
	}
	return (TRUE);
}

static void	chdir_error(char *tmp)
{
	printf("minishell : cd : %s : No such file or directory\n", tmp);
	data.exit_status = 1;
}

static void	update_pwd(void)
{
	update_pwd_oldpwd("OLDPWD");
	update_pwd_oldpwd("PWD");
}