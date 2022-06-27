/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:17 by yukim             #+#    #+#             */
/*   Updated: 2022/06/27 12:25:07 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
printf => write(fd, buf, len) 로 바꾸기
echo "hi" > a.txt > b.txt

*/

static int	do_echo(t_astnode *args_node, int option_flag);

int	ft_echo(t_astnode *args_node)
{
	int	*arg;
	int	option_flag;

	// if (!data)
	// 	return (ERROR);
	option_flag = FALSE;
	arg = args_node->prightchild->pvalue_index;
	while(*arg != -1)
	{
		if(data.lexer.ptype[*arg] == T_OPTION)
			option_flag = TRUE;
		arg++;
	}
	if(do_echo(args_node, option_flag) == ERROR)
		return (ERROR);
	return (TRUE);
}

static int	do_echo(t_astnode *args_node, int option_flag)
{
	int		*arg;
	char	*rm_quote_str;
	
	arg = args_node->prightchild->pvalue_index;
	arg++;
	while(*arg != -1)
	{
		if(data.lexer.ptype[*arg] == T_OPTION)
		{
			arg++;
			continue;
		}
		rm_quote_str = remove_quote(data.lexer.pptokens[*arg]);
		if(!rm_quote_str)
		{
			data.exit_status = 1;
			return (ERROR);
		}
		if(ft_strncmp(rm_quote_str, "$?", ft_strlen(rm_quote_str)))
		{
			printf("%d", data.exit_status);
			data.exit_status = 0;
		}
		else
		{
			printf("%s", rm_quote_str);
			if (*(arg + 1) != -1)
				printf(" ");
		}
		if (rm_quote_str != data.lexer.pptokens[*arg])
			free(rm_quote_str);
		arg++;
	}
	if (option_flag != TRUE)
		printf("\n");
	data.exit_status = 0;
	return (TRUE);
}
