/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:05 by yukim             #+#    #+#             */
/*   Updated: 2022/06/09 10:39:32 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exit_status_numeric_error();
static void	exit_status_argc_error();

void	ft_exit(t_data *data, t_astnode *args_node)
{
	// atoi에서 int 넘어간 범위 주면, not numeric
	// atoi 고쳐야 해
	int cnt;
	int exit_status;
	
	cnt = 0;
	while (args_node->pvalue_index[cnt] != -1)
		cnt++;
	printf("exit\n");
	if (cnt == 2)
	{
		//exit 123 num
		exit_status_argc_error(data, args_node);
		//exit asd
		exit_status_numeric_error(data, args_node);
		// arg[1]이 num인지 체크 필요 
		// num 이면 ft_atoi
	}
	else if(cnt >= 3)
	{
		exit_status_numeric_error(data, args_node);
		// arg[1]이 num인지 체크 필요 
		printf("minishell: exit :too many arguments\n");
	}
	normal_exit();
	
}

void	exit_status_numeric_error(t_data *data, t_astnode *args_node)
{
	char *str;

	str = data->plexer->pptokens[args_node->pvalue_index[1]];
	printf("exit: minishell: %s: ", str);
	printf("numeric argument required");
	exit(255);
}
static void	exit_status_argc_error(t_data *data, t_astnode *args_node)
{
	exit(1);
}
