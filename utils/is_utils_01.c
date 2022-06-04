/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:36:09 by yukim             #+#    #+#             */
/*   Updated: 2022/06/04 20:37:00 by hejang           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	is_ifs(const char c)
{
	return ((c == '\n' || c == '\t' || c == ' '));
}

int	is_redirection(const char *s)
{
	int	r_cnt;

	r_cnt = 0;
	while (*s == '<' || *s == '>')
	{
		r_cnt++;
		// 밑의 경우일 경우 에러 문구 출력 후 다음 입력 받기 (readline) 
		if (r_cnt > 2 || (r_cnt == 2 && *s != *(s - 1)))  // <>    ><   >>>>> 경우 예외처리
			return (ERROR); //// redirection ERROR : zsh: parse error near `>'
		s++;
	}
	return (r_cnt);
}

int	is_quote(const char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	return (FALSE);
}

int	is_pipe(const char *s)
{
	int	p_cnt;

	p_cnt = 0;
	while (*s == '|')
	{
		p_cnt++;
		if (p_cnt > 1)
			return (ERROR);
		s++;
	}
	return (p_cnt);
}
