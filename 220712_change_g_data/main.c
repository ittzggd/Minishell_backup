/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 17:19:47 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	start_nanoshell(t_data *data);
static int	input_str_is_not_null(t_data *data, char *input_str);
static void	input_str_is_null(void);

int	g_exit_status;

int	main(int argc, char *argv[], char **envp)
{
	t_data	data;

	(void)argv;
	if (argc == 1)
	{
		data = ft_bzero(&data, sizeof(t_data));
		init_setting(&data, envp);
		start_nanoshell(&data);
	}
	return (g_exit_status);
}

static void	start_nanoshell(t_data *data)
{
	char	*input_str;

	while (1)
	{
		reset_signal();
		reset_stdfd(data);
		input_str = readline("nanoshell $ ");
		if (input_str)
		{
			if (input_str_is_not_null(data, input_str) == CONTINUE)
			{
				add_history(input_str);
				free(input_str);
				continue ;
			}
		}
		else
			input_str_is_null();
		if (*input_str != '\0')
			add_history(input_str);
		reset_data(data);
		if (input_str)
			free(input_str);
	}
}

static int	input_str_is_not_null(t_data *data, char *input_str)
{
	if (analyze_input(data, input_str) == ERROR)
	{
		reset_data(data);
		return (CONTINUE);
	}
	init_ast(data);
	if (data.heredoc_cnt > 0)
	{
		preprocess_heredoc(data);
		if (g_exit_status == 1)
		{
			add_history(input_str);
			reset_data(data);
			return (CONTINUE);
		}
	}
	exec_ast(data);
	return (0);
}

static void	input_str_is_null(void)
{
	printf("\e[Ananoshell $ exit\n");
	exit(g_exit_status);
}
