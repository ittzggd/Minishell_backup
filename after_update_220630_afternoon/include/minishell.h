/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:44:50 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 07:04:34 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "minishell_define.h"
# include "utils.h"
# include "ast.h"
# include "builtin.h"
# include "minishell_pipe.h"
# include "minishell_red.h"

extern	t_data	data;

void	init_setting(char **envp);
int		analyze_input(char *input);

// tokens
int     tokenize_input(char *input);
char	**ft_minishell_split(const char *str);
int		ft_wordcount(char const *str);

//lexer
void		lexical_analysis(void);
void		replace_env_to_value(int i);
char		*get_envv(char *key);
t_envv_node	*get_el_node(t_envv_node *envv_list, char *key);
void		insert_envv(char *key, char *value, int init_flag);
int			init_envp(char *input, char **key, char **value);

int		syntax_analysis(void);




char	**join_filepath(char *execve_cmd);

void	free_data_lexer(void);
void	reset_data(void);
// void	free_data(void);
void	clear_linked_list(t_envv_node **p_list);
void	delete_linked_list(t_envv_node **p_list);

void	ctrl_c(int sig_num);
void	ctrl_bs(int sig_num);
void	ft_sig_handler_in_heredoc(int sig_num);
void	reset_stdfd(void);
void	reset_signal(void);

void	free_data_heredoc_fd(void);
void	free_data_heredoc_delimiter(void);

void	preprocess_heredoc(void);
void	get_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd);



void    syntax_error(int *ret_status);
void    syntax_check_command(int *curr);
void    syntax_check_option(int *curr,  int *ret_status);
void    syntax_check_redirection(int *curr, int *ret_status);
void    syntax_check_pipe(int *curr,  int *ret_status);
void    syntax_check_null(int *curr,  int *ret_status);
void	calloc_nullcheck(void **address, int count, int size);
void	free_all_in_data(void);
void	free_data_envvlist(void);
void	exec_heredoc(int i, int *idx);

int	    check_env(char	*token, int i, int j);
void	get_value(char *key, char *token, int key_len, int i, int j);
// void	get_value(char *key, char *token,char **argv, int key_len, int i, int j);
char	**create_argv(int cnt, t_astnode *argsnode);
void	command_not_found_error(char *cmd);
void	fork_before_run_execve(char **filepath, int idx, char **argv);
void	command_without_pipe(char *execve_cmd, int idx, char **argv, char **filepath);

void	_error(char *error_msg);
void	execve_cmd(t_astnode *argsnode);

#endif
