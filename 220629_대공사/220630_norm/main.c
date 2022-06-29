/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 03:25:00 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	analyze_input(char *input)
{
	tokenize_input(input);
	if (!data.lexer.pptokens)
	/*
	error
	*/
		return (ERROR);
	lexical_analysis();
	/*
	error
	*/
	if (!data.lexer.ptype)
		return (ERROR);
	if (syntax_analysis() != 0)
	{
	/*
	error
	*/
		data.exit_status = 258;
		return (ERROR);
	}
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
				if (data.heredoc_cnt > 0)
				{
					preprocess_heredoc();
					if (data.exit_status == 1)
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
				/*
				error
				*/
				// free
					// data에 있는 모든 것 free.
				exit(0);
			}
			add_history(input_str);
			reset_data();
		}

		// 종료 전 열린 파이프 닫기
		close(data.std_fd[0]);
		close(data.std_fd[1]);
		// 종료 전 data에 남은 것들 free
		//envv_list 랑 data,,,,
	}
	return (data.exit_status);
}

