/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 09:52:55 by hejang            #+#    #+#             */
/*   Updated: 2022/06/13 19:13:56 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell_define.h"

int		ft_echo(t_data *data, t_astnode *args_node);
int		ft_pwd(t_data *data);
int		ft_env(t_data *data, int export_flag);
int		ft_unset(t_data *data, t_astnode *args_node);
int		ft_export(t_data *data, t_astnode *args_node);
void	ft_exit(t_data *data, t_astnode *args_node);
int		ft_cd(t_data *data, t_astnode *args_node);

void	exit_status_numeric_error(t_data *data, t_astnode *args_node);
void	update_pwd_oldpwd(t_data *data, char *key);

#endif
