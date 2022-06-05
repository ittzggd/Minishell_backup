/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:17 by yukim             #+#    #+#             */
/*   Updated: 2022/06/03 14:14:41 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	do_echo(t_data *data, t_astnode *args_node, int option_flag);
static char	*remove_quote(char *token);

int	ft_echo(t_data *data, t_astnode *args_node)
{
	int	*arg;
	int	option_flag;

	if (!data)
		return (ERROR);
	option_flag = FALSE;
	arg = args_node->prightchild->pvalue_index;
	while(*arg != -1)
	{
		if(data->plexer->ptype[*arg] == T_OPTION)
			option_flag = TRUE;
		arg++;
	}
	if(do_echo(data, args_node, option_flag) == ERROR)
		return (ERROR);
	return (TRUE);
}

static int	do_echo(t_data *data, t_astnode *args_node, int option_flag)
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
		printf("%s", rm_quote_str);
		free(rm_quote_str);
		arg++;
	}
	if (option_flag != TRUE)
		printf("\n");
	return (TRUE);
}

static char	*remove_quote(char *token)
{
	char	*ret;
	int		len;

	ret = ft_strdup(token + 1);
	if (!ret)
		return (NULL);
	len = ft_strlen(ret);
	ret[len - 1] = '\0';
	return (ret);
}