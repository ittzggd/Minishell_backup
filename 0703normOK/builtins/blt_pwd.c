/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:39 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:09:53 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	g_data.exit_status = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		g_data.exit_status = 1;
		return (g_data.exit_status);
	}
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	return (g_data.exit_status);
}
