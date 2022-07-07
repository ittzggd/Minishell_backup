/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/07/07 12:17:50 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	start_nanoshell(void);
static int	input_str_is_not_null(char *input_str);
static void	input_str_is_null(void);
void	postorderTravelBinSTree(t_astnode *node);


void	postorderTravelBinSTree(t_astnode *node)
{
	int i = 0;

	if(node)
	{
		printf("node type : %d  ", node->nodetype);
		if(node->pvalue_index)
		{
			while(node->pvalue_index[i] != -1)
			{
				printf("       value : %s         ", g_data.lexer.pptokens[node->pvalue_index[i]]);
				i++;
			}
		}
		printf("\n");
		postorderTravelBinSTree(node->pleftchild);
		postorderTravelBinSTree(node->prightchild);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argv;
	if (argc == 1)
	{
		init_setting(envp);
		start_nanoshell();
	}
	return (g_data.exit_status);
}

static void	start_nanoshell(void)
{
	char	*input_str;

	while (1)
	{
		reset_signal();
		reset_stdfd();
		input_str = readline("nanoshell >> ");
		if (input_str)
		{
			if (input_str_is_not_null(input_str) == CONTINUE)
				continue ;
		}
		else
			input_str_is_null();
		add_history(input_str);
		reset_data();
		if (input_str)
			free(input_str);
	}
}

static int	input_str_is_not_null(char *input_str)
{
	if (analyze_input(input_str) == ERROR)
	{
		free_data_lexer();
		return (CONTINUE);
	}
	init_ast();
	postorderTravelBinSTree(g_data.ast.prootnode);
	if (g_data.heredoc_cnt > 0)
	{
		preprocess_heredoc();
		if (g_data.exit_status == 1)
		{
			add_history(input_str);
			reset_data();
			return (CONTINUE);
		}
	}
	exec_ast();
	return (0);
}

static void	input_str_is_null(void)
{
	printf("exit\n");
	exit(0);
}
