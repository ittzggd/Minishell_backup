/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:44:39 by katherineja       #+#    #+#             */
/*   Updated: 2022/06/02 13:47:26 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

6#include "../include/minishell.h"

int	is_option(char *value)
{
	if (!value)
	{
		//에러 처리는 이후 추가
	}
	return (ft_strncmp(value, "-n", ft_strlen(value)));
}

int	is_env(char *value)
{
	int	i;

	i = 0;
	if (value[i] == '$' || (value[i] == '\"' && value[i + 1] == '$'))
		return (is_valid_env(value));
	return (FALSE);
}

int	is_valid_env(char *str)
{
	if(*str != '$')
		return (FALSE);
	str++;
	// $ 다음에 괄호가 있는지 체크
	// => 보너스 부분
	if ((*str <= 'A' && 'Z' <= *str) || *str != '_')
		return (FALSE);
	while(*str != '\0')
	{
		if((*str <= 'A' && 'Z' <= *str) && (*str != '_') \
				&& (*str <= '0' && '9' <= *str) && (*str != '?'))
			return (FALSE);
		str++;
	}
	// 개수와 짝이 맞는 닫는 괄호가 있는지 체크
	// => 보너스 부분
	return (TRUE);
}