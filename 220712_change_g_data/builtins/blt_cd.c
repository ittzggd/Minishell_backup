/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:13 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 19:21:11 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	chdir_error(char *tmp);
static void	update_pwd(t_data *data);
static int	cd_home(t_data *data, char **home_path, char **dst_path, char **tmp);

int	ft_cd(t_data *data, t_astnode *args_node)
{
	char	*tmp;
	char	*dst_path;
	char	*home_path;
	int		idx;

	g_exit_status = 0;
	idx = args_node->prightchild->pvalue_index[1];
	if (idx == END)
		tmp = ft_strdup("~");
	else
		tmp = ft_strdup(data->lexer.pptokens[args_node->prightchild->pvalue_index[1]]);
	if (idx == END || ft_strncmp(tmp, "~", -1))
	{
		if (cd_home(data, &home_path, &dst_path, &tmp) == ERROR)
			return (g_exit_status);
	}
	else if (ft_strncmp(tmp, "-", -1))
		dst_path = get_envv(data, "OLDPWD");
	else
		dst_path = tmp;
	if (chdir(dst_path) == ERROR)
		chdir_error(tmp);
	else
		update_pwd(data);
	if (tmp != dst_path)
		free(dst_path);
	free(tmp);
	return (g_exit_status);
}

static int	cd_home(t_data *data, char **home_path, char **dst_path, char **tmp)
{
	*home_path = get_envv(data, "HOME");
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
	ft_error_message(": No such file or directory\n", 1);
}

static void	update_pwd(t_data *data)
{
	char	*tmp;
	char	*key;

	tmp = data->current_path;
	key = ft_strdup("OLDPWD");
	update_pwd_oldpwd(data, key);
	key = ft_strdup("PWD");
	update_pwd_oldpwd(data, key);
	data->current_path = get_envv("PWD");
	if (!data->current_path)
		data->current_path = getcwd(NULL, 0);
	if (tmp != data->current_path)
		free(tmp);
}
