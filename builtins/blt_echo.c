/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:17 by yukim             #+#    #+#             */
/*   Updated: 2022/06/13 12:41:48 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
printf => write(fd, buf, len) 로 바꾸기
echo "hi" > a.txt > b.txt

*/

static int	do_echo(t_data *data, t_astnode *args_node, int option_flag, int fd);

int	ft_echo(t_data *data, t_astnode *args_node, int fd)
{
	int	*arg;
	int	option_flag;

	if (fd < 0)
	{
		data->exit_status = 1;
		return (ERROR);
	}	
	option_flag = FALSE;
	arg = args_node->prightchild->pvalue_index;
	while(*arg != -1)
	{
		if(data->plexer->ptype[*arg] == T_OPTION)
			option_flag = TRUE;
		arg++;
	}
	if(do_echo(data, args_node, option_flag, fd) == ERROR)
		return (ERROR);
	return (TRUE);
}

static int	do_echo(t_data *data, t_astnode *args_node, int option_flag, int fd)
{
	int		*arg;
	char	*rm_quote_str;
	
	arg = args_node->prightchild->pvalue_index;
	arg++;
	while(*arg != -1)
	{
		if(data->plexer->ptype[*arg] == T_OPTION)
		{
			arg++;
			continue;
		}
		rm_quote_str = remove_quote(data->plexer->pptokens[*arg]);
		if(!rm_quote_str)
			return (ERROR);
		if(ft_strncmp(rm_quote_str, "$?", ft_strlen(rm_quote_str)))
		{
			write(fd, data->exit_status, sizeof(int));
			// printf("%d", data->exit_status);
			data->exit_status = 0;
		}
		else
		{
			write(fd, rm_quote_str, ft_strlen(rm_quote_str));
			if (*(arg + 1) != -1)
				write(fd, " ", 1);
		}
		free(rm_quote_str);
		arg++;
	}
	if (option_flag != TRUE)
		write(fd, "\n", 1);
	return (TRUE);
}
