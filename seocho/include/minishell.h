/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:44:50 by hejang            #+#    #+#             */
/*   Updated: 2022/06/26 19:18:07 by hejang           ###   ########.fr       */
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
# include "tree_utils.h"
# include "builtin.h"
# include "minishell_pipe.h"
# include "minishell_red.h"

extern	t_data		data;

void	init_setting(char **envp);
int		analyze_input(char *input);

// tokens
char	*tokenize_input(char *input);
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


char	*envv_join(char *key, char *value);
char	**envvlist_to_envp(void);

char	**join_filepath(char *execve_cmd);

void	free_data_lexer(void);
void	clear_linked_list(t_envv_node **p_list);
void	delete_linked_list(t_envv_node **p_list);

void	ft_sig_handler(int sig_num);
void	ft_heredoc_sig_handler(int sig_num);

#endif
