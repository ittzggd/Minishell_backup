/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:11:47 by yukim             #+#    #+#             */
/*   Updated: 2022/06/13 12:20:50 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "string.h"

int	ft_pipe_main()
{
	// int		**fd;
	// int		i;

	// i = 0;
	// // int fd[3][2]
	// fd = (int **)malloc(sizeof(int *) * (data->pipe_cnt + 1));
	// if (!fd)
	// 	return (ERROR);
	// while (i < (data->pipe_cnt + 1))
	// {
	// 	fd[i] = (int *)malloc(sizeof(int) * 2);
	// 	if (fd[i])
	// 		return (ERROR);
	// 	if (pipe(fd[i]) < 0)
	// 		return (ERROR);

	// }
	int pid1;
	int pid2;

	pid1 = fork();
	if (pid1 < 0) { return 1;}
	if (pid1 == 0)
	{
		
	}
	else
	{
		pid2 = fork();
	}
}

int	main()
{
	int fd[2];
	int pid;
	
	
	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		close(fd[0]);
		int	i;
		scanf(" %d", &i);
		printf("input : %d\n", i);
		write(fd[1], &i, sizeof(int));
		printf("I'm Child Process\n");
		close(fd[1]);
		return (0);
	}
	else
	{
		close(fd[1]);
		int j;
		read(fd[0], &j, sizeof(int));
		close(fd[0]);
		printf("I'm parent Process  j = %d\n", j);
	}


	return (0);
}

