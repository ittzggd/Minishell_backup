/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:39 by yukim             #+#    #+#             */
/*   Updated: 2022/06/15 19:41:33 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	data.exit_status = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		data.exit_status = 1;
		return (data.exit_status);
	}
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	data.exit_status = 0;
	return (data.exit_status);
}
