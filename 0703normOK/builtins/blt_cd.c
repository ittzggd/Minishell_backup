/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:13 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:08:34 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	chdir_error(char *tmp);
static void	update_pwd(void);
static void	free_rm_quote_str(char *rm_quote_tmp, char *dst_path);
static int	cd_home(char **home_path, char **dst_path, char **rm_quote_tmp);

int	ft_cd(t_astnode *args_node)
{
	char	*tmp;
	char	*rm_quote_tmp;
	char	*dst_path;
	char	*home_path;
	int		idx;

	g_data.exit_status = 0;
	tmp = g_data.lexer.pptokens[args_node->prightchild->pvalue_index[1]];
	rm_quote_tmp = remove_quote(tmp);
	idx = args_node->prightchild->pvalue_index[1];
	if (idx == END || ft_strncmp(rm_quote_tmp, "~", -1))
	{
		if (cd_home(&home_path, &dst_path, &rm_quote_tmp) == ERROR)
			return (g_data.exit_status);
	}
	else if (ft_strncmp(rm_quote_tmp, "-", -1))
		dst_path = get_envv("OLDPWD");
	else
		dst_path = rm_quote_tmp;
	if (chdir(dst_path) == ERROR)
		chdir_error(tmp);
	else
		update_pwd();
	free_rm_quote_str(rm_quote_tmp, dst_path);
	return (g_data.exit_status);
}

static int	cd_home(char **home_path, char **dst_path, char **rm_quote_tmp)
{
	*home_path = get_envv("HOME");
	*dst_path = ft_strjoin(*home_path, *rm_quote_tmp + 1);
	if (!home_path)
	{
		chdir_error(*dst_path);
		return (ERROR);
	}
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
}

static void	free_rm_quote_str(char *rm_quote_tmp, char *dst_path)
{
	if (dst_path)
		free(dst_path);
	if (rm_quote_tmp)
		free(rm_quote_tmp);
}
