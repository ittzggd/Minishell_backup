/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:39 by yukim             #+#    #+#             */
/*   Updated: 2022/06/05 15:50:30 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updata_pwd_oldpwd(t_data *data, char *pwd_value)
{
	char *oldpwd_value;
	oldpwd_value = get_envv(data, "OLDPWD");
	if (oldpwd_value)
		free(oldpwd_value);
	oldpwd_value = get_envv(data, "PWD");
	insert_envv(data, "OLDPWD", pwd_value);
	insert_envv(data, "PWD", pwd_value);
}

int	ft_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ERROR);
	printf("%s\n", cwd);
	// 환경변수 PWD초기화?? 재설정?? => OLD PWD 관련.
	// env.c 파일에 생성하기
	updata_pwd_oldpwd(data, cwd);
	free(cwd);
	return (TRUE);
}
