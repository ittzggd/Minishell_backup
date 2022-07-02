/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:12:30 by yukim             #+#    #+#             */
/*   Updated: 2022/07/02 18:40:25 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PIPE_H
# define MINISHELL_PIPE_H

# include <fcntl.h> //open read
# include <unistd.h> // dup, pipe, execve
# include <sys/wait.h> //wait, waitpid
# include <sys/types.h> // pid_t
// # include <dirent.h> //opendir closedir readdir

void	exec_ast(void);
void	exec_cmd(t_astnode *argsnode);


#endif 
