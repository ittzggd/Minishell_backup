/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:44:50 by hejang            #+#    #+#             */
/*   Updated: 2022/06/04 21:29:20 by hejang           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include "utils.h"
# include "minishell_define.h"
# include "tree_utils.h"

int		analyze_input(char *input);

// tokens
char	*tokenize_input(t_data *data, char *input);
char	**ft_minishell_split(const char *str);
int		ft_wordcount(char const *str);

//lexer
void	lexical_analysis(t_data *data);
t_cmd	*create_cmd_struct(void);
void	replace_env_to_word(int i, t_data *data);

void	syntax_analysis(t_data *data);

//built in
int		ft_echo(t_data *data, t_astnode *args_node);
int		ft_pwd(void);

#endif
