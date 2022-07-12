/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:44:50 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 19:18:03 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <dirent.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "minishell_define.h"
# include "utils.h"
# include "ast.h"
# include "builtin.h"
# include "minishell_red.h"

     // extern t_data	data;
extern int	g_exit_status;

void		init_setting(t_data *data, char **envp);
int			analyze_input(t_data *data, char *input);

// tokens
int			tokenize_input(t_data *data, char *input);
char		**ft_minishell_split(const char *str);
int			ft_wordcount(char const *str);
int			get_wc(char const *str, int *i, int *wc_flag, int *wc);

//lexer
void		lexical_analysis(t_data *data);
char		*get_envv(t_data *data, char *key);
t_envv_node	*get_el_node(t_envv_node *envv_list, char *key);
void		insert_envv(t_data *data, char *key, char *value, int init_flag);
int			init_envp(t_data *data, char *input, char **key, char **value);

int			syntax_analysis(t_data *data);
void		syntax_error(int *ret_status);
void		syntax_check_command(t_data *data, int *curr);
void		syntax_check_redirection(t_data *data, int *curr, int *ret_status);
void		syntax_check_pipe(t_data *data, int *curr, int *ret_status);
void		syntax_check_null(t_data *data, int *curr, int *ret_status);

void		replace_quote_env(t_data *data);

// heredoc
void		preprocess_heredoc(t_data *data);
void		exec_heredoc(t_data *data, int i, int *idx);
void		get_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd);

// exec
void		exec_ast(t_data *data);
void		exec_cmd(t_data *data, t_astnode *argsnode);
void		execve_cmd(t_data *data, t_astnode *argsnode);
char		**join_filepath(char *execve_cmd);
char		**create_argv(int cnt, t_astnode *argsnode);
void		cmd_without_pipe(char *cmd, int idx, char **argv, char *execve_cmd);
void		fork_before_run_execve(int idx, char **argv, char *execve_cmd);
void		fork_before_run_execve_child(int idx, char *ecve_cmd, char **argv);
char		**allocate_empty_str_in_filepath(void);
void		command_not_found_error(char *cmd);

// signal
void		ctrl_c(int sig_num);
void		ctrl_bs(int sig_num);
void		ft_sig_handler_in_heredoc_sigint(int sig_num);
void		ft_sig_handler_in_heredoc_sigquit(int sig_num);

// reset, free
void		free_data_heredoc_fd(t_data *data);
void		free_data_heredoc_delimiter(t_data *data);
void		free_data_lexer(t_data *data);
void		reset_data(t_data *data);
void		reset_stdfd(t_data *data);
void		reset_signal(void);

#endif
