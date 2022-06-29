/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:44:36 by yukim             #+#    #+#             */
/*   Updated: 2022/06/30 06:46:31 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	preprocess_heredoc(void)
{
	char	*delimiter;
	int		i;
	int		idx;
	int		len;

	data.heredoc_flag = TRUE;
	data.exit_status = 0;
	data.heredoc_delimiter = ft_calloc(data.heredoc_cnt + 1, sizeof(char *));
	if (!data.heredoc_delimiter)
	{
		free_all_in_data();
		exit(1);
	}
	calloc_nullcheck(&data.heredoc_fd, data.heredoc_cnt, sizeof(t_heredoc_fd *));
	i = 0;
	idx = 0;
	while (idx < data.heredoc_cnt)
	{
		if (data.lexer.ptype[i] == T_REDIRECTION)
			exec_heredoc(i, &idx);
		i++;
	}
	data.heredoc_delimiter[idx] = NULL;
	data.heredoc_flag = FALSE;
}
