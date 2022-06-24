/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:39 by yukim             #+#    #+#             */
/*   Updated: 2022/06/10 17:23:37 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_data *data)
{
	char	*cwd;

	data->exit_status = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		data->exit_status = 1;
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	return (data->exit_status);
}
