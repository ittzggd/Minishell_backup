/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:40:41 by yukim             #+#    #+#             */
/*   Updated: 2022/05/26 21:08:53 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_minishell_split(char const *str)
{
	int		wc;
	char	**ret;

	if (!str)
		return (NULL);
	wc = ft_wordcount(str);
	if (wc == ERROR)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * wc);
	/*
	1. 단어 개수 세기
	2. ret malloc => NULL 체크
	3. ret 배열에 붙여 넣을 때, 단어마다 malloc => NULL 체크 => copy
	4. 실패시 free
	*/
	return (ret);
}