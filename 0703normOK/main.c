/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/07/03 17:31:33 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	analyze_input(char *input)
{
	if (tokenize_input(input) == ERROR)
		return (ERROR);
	lexical_analysis();
	if (syntax_analysis() != 0)
		return (ERROR);
	return (TRUE);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*input_str;

	if (argc == 1)
	{
		init_setting(envp);
		while (1)
		{
			reset_signal();
			reset_stdfd();
			input_str = readline("nanoshell >> ");
			if (input_str)
			{
				if (analyze_input(input_str) == ERROR)
				{
					free_data_lexer();
					continue ;
				}
				init_ast();
				if (g_data.heredoc_cnt > 0)
				{
					preprocess_heredoc();
					if (g_data.exit_status == 1)
					{
						add_history(input_str);
						reset_data();
						continue ;
					}
				}
				exec_ast();
		}
			else
			{
				printf("exit\n");
				exit(0);
			}
			add_history(input_str);
			reset_data();
			if (input_str)
				free(input_str);
		}
		close(g_data.std_fd[0]);
		close(g_data.std_fd[1]);
	}
	return (g_data.exit_status);
}
