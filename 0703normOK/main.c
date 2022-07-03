/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/07/03 18:31:41 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	start_nanoshell(void);
static int	input_str_is_not_null(char *input_str);
static void	input_str_is_null(void);

int	main(int argc, char *argv[], char **envp)
{
	if (argc == 1)
	{
		init_setting(envp);
		start_nanoshell();
		// close(g_data.std_fd[0]); 
		// close(g_data.std_fd[1]);
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