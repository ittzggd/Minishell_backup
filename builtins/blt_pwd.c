/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:39 by yukim             #+#    #+#             */
/*   Updated: 2022/06/03 15:00:31 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ERROR);
	printf("%s\n", cwd);
	// 환경변수 PWD초기화?? 재설정?? => OLD PWD 관련.
	// env.c 파일에 생성하기
	free(cwd);
	return (TRUE);
}