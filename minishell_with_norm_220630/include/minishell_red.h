/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_red.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:55:50 by yukim             #+#    #+#             */
/*   Updated: 2022/06/29 19:58:34 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_RED_H
# define MINISHELL_RED_H

# include <fcntl.h>

void	out_red(char *filename);
void	in_red(char *filename);
void	append_red(char *filename);
void	heredoc(char *delimiter);

void	goto_redirection(t_astnode *red_node);
void	postorder_travel_reds(t_astnode *reds_node);
void	postorder_travel_command(t_astnode *cmdnode);
void	postorder_travel_ast(t_astnode *ast_node);

#endif
