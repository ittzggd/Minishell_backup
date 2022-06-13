/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:53:01 by katherineja       #+#    #+#             */
/*   Updated: 2022/05/27 22:53:01 by katherineja      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	set_cmd(char **cmd, int i)
{
	if (i == 0)
		cmd[0] = ft_strdup("echo");
	else if (i == 1)
		cmd[1] = ft_strdup("cd");
	else if (i == 2)
		cmd[2] = ft_strdup("pwd");
	else if (i == 3)
		cmd[3] = ft_strdup("export");
	else if (i == 4)
		cmd[4] = ft_strdup("unset");
	else if (i == 5)
		cmd[5] = ft_strdup("env");
	else if (i == 6)
		cmd[6] = ft_strdup("exit");
	else if (i == 7)
		cmd[7] = ft_strdup("minishell");
}

t_cmd	*create_cmd_struct(void)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	while (i < 8)
	{
		set_cmd(cmd->cmd, i);
		if (!cmd->cmd[i])
		{
			ft_free_all(cmd->cmd);
			return (NULL);
		}
		i++;
	}
	cmd->cmd[8] = NULL;
	return (cmd);
}
