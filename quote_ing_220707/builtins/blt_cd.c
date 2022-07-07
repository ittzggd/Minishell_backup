/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:13 by yukim             #+#    #+#             */
/*   Updated: 2022/07/07 21:10:58 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	chdir_error(char *tmp);
static void	update_pwd(void);
// static void	free_rm_quote_str(char *rm_quote_tmp, char *dst_path);
static int	cd_home(char **home_path, char **dst_path, char **tmp);

int	ft_cd(t_astnode *args_node)
{
	char	*tmp;
	// char	*rm_quote_tmp;
	char	*dst_path;
	char	*home_path;
	int		idx;

	g_data.exit_status = 0;
	tmp = g_data.lexer.pptokens[args_node->prightchild->pvalue_index[1]];
	// rm_quote_tmp = remove_quote(tmp);
	idx = args_node->prightchild->pvalue_index[1];
	if (idx == END || ft_strncmp(tmp, "~", -1))
	{
		if (cd_home(&home_path, &dst_path, &tmp) == ERROR)
			return (g_data.exit_status);
	}
	else if (ft_strncmp(tmp, "-", -1))
		dst_path = get_envv("OLDPWD");
	else
		dst_path = tmp;
	if (chdir(dst_path) == ERROR)
		chdir_error(tmp);
	else
		update_pwd();
	// free_rm_quote_str(tmp, dst_path);
	return (g_data.exit_status);
}

static int	cd_home(char **home_path, char **dst_path, char **tmp)
{
	*home_path = get_envv("HOME");
	*dst_path = ft_strjoin(*home_path, *tmp + 1);
	if (!home_path)
	{
		free(*tmp);
		chdir_error(*dst_path);
		return (ERROR);
	}
	free(*home_path);
	return (TRUE);
}

static void	chdir_error(char *tmp)
{
	ft_error_message("minishell : cd : ", 1);
	ft_error_message(tmp, 1);
	ft_error_message("No such file or directory\n", 1);
}

static void	update_pwd(void)
{
	update_pwd_oldpwd("OLDPWD");
	update_pwd_oldpwd("PWD");
	g_data.current_path = get_envv("PWD");
	if (!g_data.current_path)
		g_data.current_path = getcwd(NULL, 0);
}

// static void	free_rm_quote_str(char *rm_quote_tmp, char *dst_path)
// {
//  	if (dst_path == rm_quote_tmp)
//  		free(dst_path);
//  	else
// 	{
//  		free(rm_quote_tmp);
// 		free(dst_path);
// 	}
//  }
