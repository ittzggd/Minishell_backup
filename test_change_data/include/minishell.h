/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:44:50 by hejang            #+#    #+#             */
/*   Updated: 2022/06/15 19:35:56 by hejang           ###   ########.fr       */
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
# include "minishell_define.h"
# include "utils.h"
# include "tree_utils.h"
# include "builtin.h"
# include "minishell_pipe.h"
# include "minishell_red.h"

extern	t_data		data;

int		analyze_input(char *input);

// tokens
char	*tokenize_input(char *input);
char	**ft_minishell_split(const char *str);
int		ft_wordcount(char const *str);

//lexer
void		lexical_analysis(void);
t_cmd		*create_cmd_struct(void);
void		replace_env_to_value(int i);
char		*get_envv(char *key);
t_envv_node	*get_el_node(t_envv_node *envv_list, char *key);
void		insert_envv(char *key, char *value, int init_flag);
int			init_envp(char *input, char **key, char **value);

int		syntax_analysis(void);




#endif
