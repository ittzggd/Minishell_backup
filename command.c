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

#include "minishell.h"

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
}

t_cmd	*create_cmd_struct(void)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	while (i < 7)
	{
		set_cmd(cmd->cmd, i);
		if (!cmd->cmd[i])
		{
			ft_free_all(cmd->cmd);
			return (NULL);
		}
	}
	cmd->cmd[7] = NULL;
	return (cmd);
}

int	is_cmd(char *value)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = create_cmd_struct();
	if (!cmd)
	{
		// 에러 부분을 플로우차트 작성해서 따로 빼주기
		// 에러메세지를 출력해주자
		// 이전에 malloc된 부분들을 free
	}
	while (cmd->cmd[i])
	{
		if (ft_strncmp(value, cmd->cmd[i], ft_strlen(value)))
			return (TRUE);
		i++;
	}
	return (FALSE);
}