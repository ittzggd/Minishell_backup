/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:17 by yukim             #+#    #+#             */
/*   Updated: 2022/06/29 23:30:15 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	do_echo(t_astnode *args_node);
static void	do_echo_dollor_question_mark(void);
static void	do_echo_print(int *arg, char *rm_quote_str);

int	ft_echo(t_astnode *args_node)
{
	int	*arg;
	int	option_flag;

	option_flag = FALSE;
	arg = args_node->prightchild->pvalue_index;
	while (*arg != END)
	{
		if (data.lexer.ptype[*arg] == T_OPTION)
			option_flag = TRUE;
		arg++;
	}
	do_echo(args_node, option_flag);
	if (option_flag != TRUE)
		printf("\n");
	data.exit_status = 0;
	return (TRUE);
}

static int	do_echo(t_astnode *args_node)
{
	int		*arg;
	char	*rm_quote_str;
	
	arg = args_node->prightchild->pvalue_index;
	arg++;
	while(*arg != END)
	{
		if(data.lexer.ptype[*arg] == T_OPTION)
		{
			arg++;
			continue;
		}
		rm_quote_str = remove_quote(data.lexer.pptokens[*arg]);
		if(ft_strncmp(rm_quote_str, "$?", ft_strlen(rm_quote_str)))
			do_echo_dollor_question_mark();
		else
			do_echo_print(arg, rm_quote_str);
		if (rm_quote_str != data.lexer.pptokens[*arg])
			free(rm_quote_str);
		arg++;
	}
	return (TRUE);
}

static void	do_echo_dollor_question_mark(void)
{
	printf("%d", data.exit_status);
	data.exit_status = 0;
}

static void	do_echo_print(int *arg, char *rm_quote_str)
{
	printf("%s", rm_quote_str);
	if (*(arg + 1) != END)
		printf(" ");
}
